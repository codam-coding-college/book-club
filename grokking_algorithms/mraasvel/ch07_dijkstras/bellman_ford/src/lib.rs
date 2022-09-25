use std::{borrow::Cow, collections::HashMap, fmt::Display};

#[derive(Debug)]
pub struct ResultVertex<'a> {
    pub id: &'a str,
    pub previous: &'a str,
    pub distance: isize,
}

#[derive(Debug)]
pub struct Error {
    message: Cow<'static, str>,
}

impl Error {
    fn borrowed(message: &'static str) -> Error {
        Error {
            message: Cow::Borrowed(message),
        }
    }

    fn owned(message: String) -> Error {
        Error {
            message: Cow::Owned(message),
        }
    }
}

impl Display for Error {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.message)
    }
}

impl std::error::Error for Error {}

#[derive(Debug)]
pub struct Edge<'a> {
    pub vertex: &'a str,
    pub weight: isize,
}

#[derive(Debug)]
pub struct Vertex<'a> {
    pub id: &'a str,
    pub edges: Vec<Edge<'a>>,
}

#[derive(Debug)]
struct Distance<'a> {
    previous: Option<&'a str>,
    distance: Option<isize>,
}

pub fn bellman_ford<'a>(
    start: &str,
    vertices: &Vec<Vertex<'a>>,
) -> Result<Vec<ResultVertex<'a>>, Error> {
    if vertices.is_empty() {
        return Err(Error::borrowed("require at least one vertex"));
    }
    let mut distances: HashMap<_, _> = vertices
        .iter()
        .map(|vertex| {
            (
                vertex.id,
                Distance {
                    previous: None,
                    distance: None,
                },
            )
        })
        .collect();

    distances
        .get_mut(start)
        .ok_or_else(|| Error::borrowed("start node not present in vertices"))?
        .distance = Some(0);

    for _ in 0..vertices.len() - 1 {
        let mut changed = false;
        for (vertex, edge) in vertices
            .iter()
            .flat_map(|vertex| vertex.edges.iter().map(|edge| (vertex.id, edge)))
        {
            let dist_a = distances.get(vertex).unwrap().distance;
            let b = distances
                .get_mut(edge.vertex)
                .ok_or_else(|| Error::owned(format!("vertex: {}: not found", edge.vertex)))?;
            match (dist_a, b.distance) {
                (Some(dist_a), dist_b)
                    if dist_b
                        .map(|dist_b| dist_a + edge.weight < dist_b)
                        .unwrap_or(true) =>
                {
                    b.distance = Some(dist_a + edge.weight);
                    b.previous = Some(vertex);
                    changed = true;
                }
                _ => {}
            }

            if !changed {
                break;
            }
        }
    }
    Ok(distances
        .into_iter()
        .filter_map(|(id, data)| {
            if let Some(previous) = data.previous {
                Some(ResultVertex {
                    id,
                    previous,
                    distance: data.distance?,
                })
            } else {
                // skip start in results
                None
            }
        })
        .collect())
}
