use std::collections::{HashMap, HashSet};

pub type Edge<'a> = (&'a str, usize);

#[derive(Debug)]
struct NodeData<'a> {
    cost: usize,
    previous: Option<&'a str>,
}

type NodeDataMap<'a, 'b> = HashMap<&'a str, NodeData<'b>>;

pub fn solve<'a>(
    start: &'a str,
    goal: &'a str,
    graph: &HashMap<&'a str, Vec<Edge<'a>>>,
) -> Vec<&'a str> {
	let mut nodes = NodeDataMap::<'a, 'a>::new();
    nodes.insert(
        start,
        NodeData {
            cost: 0,
            previous: None,
        },
    );
    let mut processed = HashSet::new();
    loop {
        // get lowest cost node
        let (&name, &NodeData { cost, .. }) = nodes
            .iter()
            .filter(|(&name, _)| !processed.contains(name))
            .min_by_key(|(_, node)| node.cost)
            .unwrap();
        if name == goal {
            break;
        }
        // update neighbours as appropriate
        for (edge, weight) in graph.get(name).unwrap() {
            let new_cost = weight + cost;
            nodes
                .entry(edge)
                .and_modify(|node| {
                    if new_cost < node.cost {
                        node.cost = new_cost;
                        node.previous = Some(name);
                    }
                })
                .or_insert_with(|| NodeData {
                    cost: new_cost,
                    previous: Some(name),
                });
        }
        processed.insert(name);
    }
    // construct history
    let mut result = vec![goal];
    let mut node = nodes.get(goal).unwrap();
    while let Some(&prev) = node.previous.as_ref() {
        result.push(prev);
        node = nodes.get(prev).unwrap();
    }
    result.reverse();
    result
}
