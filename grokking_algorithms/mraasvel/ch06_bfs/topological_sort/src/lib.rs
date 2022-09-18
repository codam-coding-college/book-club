use std::collections::HashMap;

pub struct Node {
    connections: Vec<String>,
}

impl Node {
    pub fn new(connections: Vec<String>) -> Node {
        Node { connections }
    }
}

struct NodeWithDegree<'a> {
    node: &'a Node,
    degree: usize,
}

// invariants:
// 1. graph is a directed acyclic graph
// 2. each connected node should itself be a key in the hashmap
pub fn topological_sort<'a>(graph: &'a HashMap<String, Node>) -> Vec<String> {
    // 1. compute degree of each node: (its dependency count) O(V + E), number of vertices + number of edges
    let mut degrees: HashMap<&str, NodeWithDegree<'a>> = HashMap::new();
    graph.into_iter().for_each(|(name, node)| {
        degrees
            .entry(name)
            .and_modify(|nwd| nwd.node = node)
            .or_insert(NodeWithDegree { node, degree: 0 });
        // add one degree to each of its neighbours
        // if not present insert with 1 and arbitrary node reference which will be updated later
        node.connections.iter().for_each(|name| {
            assert!(graph.contains_key(name));
            degrees
                .entry(name)
                .and_modify(|nwd| nwd.degree += 1)
                .or_insert(NodeWithDegree { node, degree: 1 });
        });
    });

    // 2. create the stack containing all the nodes with a degree of 0
    let mut to_visit = Vec::new(); // we can actually use a stack because the ordering of same-degree nodes is irrelevant
    degrees.iter().for_each(|(name, node)| {
        if node.degree == 0 {
            to_visit.push(*name);
        }
    });

    // 3. create the sorted vector
    // for each 'root' node in the current graph we subtract 1 from the degree (dependencies) of its connections
    let mut result = Vec::new();
    while let Some(next) = to_visit.pop() {
        result.push(next.to_string());
        let node = degrees.get(next).unwrap();
        node.node.connections.iter().for_each(|name| {
            let node = degrees.get_mut(name.as_str()).unwrap();
            assert_ne!(node.degree, 0);
            node.degree -= 1;
            if node.degree == 0 {
                to_visit.push(name.as_str());
            }
        })
    }
    result
}
