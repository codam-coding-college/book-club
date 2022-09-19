use std::{
    collections::{HashMap, HashSet},
    hash::Hash,
};

pub type Edge<T> = (T, usize);

#[derive(Debug)]
struct NodeData<T> {
    cost: usize,
    previous: Option<T>,
}

type NodeDataMap<T> = HashMap<T, NodeData<T>>;

fn find_lowest_cost_node<'a, T>(nodes: &'a NodeDataMap<T>, processed: &HashSet<T>) -> (&'a T, usize)
where
    T: Hash + Eq + Clone,
{
    nodes
        .iter()
        .filter(|(name, _)| !processed.contains(name))
        .min_by_key(|(_, node)| node.cost)
        .map(|(name, node)| (name, node.cost))
        .unwrap()
}

fn construct_history<T>(goal: T, nodes: &NodeDataMap<T>) -> Vec<T>
where
    T: Hash + Eq + Clone,
{
    let mut node = nodes.get(&goal).unwrap();
    let mut history = vec![goal];
    while let Some(prev) = node.previous.as_ref() {
        history.push(prev.clone());
        node = nodes.get(prev).unwrap();
    }
    history.reverse();
    history
}

fn update_connections<T>(
    name: T,
    cost: usize,
    nodes: &mut NodeDataMap<T>,
    graph: &HashMap<T, Vec<Edge<T>>>,
) where
    T: Hash + Eq + Clone,
{
    for (edge, weight) in graph.get(&name).unwrap() {
        let edge = edge.clone();
        let new_cost = weight + cost;
        nodes
            .entry(edge)
            .and_modify(|node| {
                if new_cost < node.cost {
                    node.cost = new_cost;
                    node.previous = Some(name.clone());
                }
            })
            .or_insert_with(|| NodeData {
                cost: new_cost,
                previous: Some(name.clone()),
            });
    }
}

pub fn solve<T>(start: T, goal: T, graph: &HashMap<T, Vec<Edge<T>>>) -> Vec<T>
where
    T: Hash + Eq + Clone,
{
    let mut nodes = NodeDataMap::<T>::new();
    nodes.insert(
        start,
        NodeData {
            cost: 0,
            previous: None,
        },
    );
    let mut processed = HashSet::new();
    loop {
        let (name, cost) = find_lowest_cost_node(&nodes, &processed);
        if name == &goal {
            break;
        }
        processed.insert(name.clone());
        update_connections(name.clone(), cost, &mut nodes, graph);
    }
    construct_history(goal, &nodes)
}
