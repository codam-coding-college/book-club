use std::collections::HashSet;

#[derive(Debug)]
pub struct Error {
    message: &'static str,
}

impl std::error::Error for Error {}

impl std::fmt::Display for Error {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.message)
    }
}

#[derive(Debug)]
pub struct RadioStation<'a, 'b> {
    pub id: &'a str,
    pub states: HashSet<&'b str>,
}

fn num_states_covered(
    states: &HashSet<&str>,
    covered: &HashSet<&str>,
    station: &RadioStation,
) -> usize {
    station
        .states
        .difference(covered)
        .filter(|&state| states.contains(state))
        .count()
}

/// returns the index of the station that covers the most uncovered states
fn find_best_station(
    states: &HashSet<&str>,
    covered: &HashSet<&str>,
    stations: &[RadioStation],
) -> Option<usize> {
    assert!(!stations.is_empty());
    stations
        .iter()
        .enumerate()
        .fold(None, |pair, (index, station)| {
            let covered = num_states_covered(states, covered, station);
            match pair {
                Some((best_index, num_covered)) => {
                    if covered > num_covered {
                        Some((index, covered))
                    } else {
                        Some((best_index, num_covered))
                    }
                }
                None => {
                    if covered > 0 {
                        Some((index, covered))
                    } else {
                        None
                    }
                }
            }
        })
        .map(|opt| opt.0)
}

/// Radio stations cover the stations in to_cover
/// This function returns the least amount of radio stations needed to cover the full set of states
/// Since it is a greedy algorithm, it is not guaranteed to find the optimal solution
///
/// 1. Find the station that covers the most states not yet covered.
/// 2. Add the states to the `covered` set and remove the station from the table.
pub fn greedy_set_covering_problem<'a, 'b, 'c>(
    states: &HashSet<&'a str>,
    mut stations: Vec<RadioStation<'b, 'c>>,
) -> Result<Vec<RadioStation<'b, 'c>>, Error> {
    let mut covered = HashSet::new();
    let mut used = Vec::new();
    while covered.len() != states.len() {
        if stations.is_empty() {
            return Err(Error {
                message: "no stations left despite some states being uncovered",
            });
        }
        let index = find_best_station(states, &covered, &stations).ok_or(Error {
            message: "none of the remaining states can cover the remaining states",
        })?;
        let station = stations.swap_remove(index);
        covered.extend(
            station
                .states
                .iter()
                .filter(|&state| states.contains(state)),
        );
        used.push(station);
    }
    Ok(used)
}
