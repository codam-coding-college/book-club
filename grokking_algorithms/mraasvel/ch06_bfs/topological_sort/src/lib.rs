use std::collections::HashMap;

#[derive(Debug)]
pub struct Node {
    dependencies: Vec<String>,
}

impl Node {
    pub fn new(dependencies: Vec<String>) -> Node {
        Node { dependencies }
    }
}

#[derive(Debug, Clone)]
struct NodeWithDegree<'a> {
    connections: Vec<&'a str>,
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
            .and_modify(|nwd| nwd.degree = node.dependencies.len())
            .or_insert(NodeWithDegree { connections: Vec::new(), degree: node.dependencies.len() });
        // this node is dependent on other nodes, meaning the other nodes point to this one
        node.dependencies.iter().for_each(|dep| {
            assert!(graph.contains_key(dep));
            degrees
                .entry(dep)
                .and_modify(|nwd| nwd.connections.push(name.as_str()))
                .or_insert_with(|| NodeWithDegree { connections: vec![name.as_str()], degree: 0 });
        });
    });

    dbg!(&degrees);
    // 2. create the stack containing all the nodes with a degree of 0
    let mut to_visit = Vec::new(); // we can actually use a stack because the ordering of same-degree nodes is irrelevant
    degrees.iter().for_each(|(name, node)| {
        if node.degree == 0 {
            to_visit.push(*name);
        }
    });

    // 3. create the sorted vector
    // for each 'root' node in the current graph we subtract 1 from the degree (connections) of its connections
    let mut result = Vec::new();
    while let Some(next) = to_visit.pop() {
        result.push(next.to_string());
        let node = degrees.get(next).unwrap().clone();
        node.connections.iter().for_each(|&name| {
            let node = degrees.get_mut(name).unwrap();
            assert_ne!(node.degree, 0);
            node.degree -= 1;
            if node.degree == 0 {
                to_visit.push(name);
            }
        })
    }
    result
}
