use std::collections::HashMap;
use std::iter::FromIterator;

use topological_sort::topological_sort;
use topological_sort::Node;

fn main() {
    let graph = HashMap::from_iter(
        [
            ("get dressed", vec!["wake up"]),
            ("brush teeth", vec!["wake up"]),
            ("wake up", vec![]),
            ("go to work", vec!["get dressed", "brush teeth"]),
        ]
        .into_iter()
        .map(|(key, connections)| {
            let node = Node::new(connections.into_iter().map(String::from).collect());
            (key.to_string(), node)
        }),
    );

    let result = topological_sort(&graph);
    dbg!(&result);
    assert_eq!(result[0], "wake up");
    assert!(result[1] == "brush teeth" || result[1] == "get dressed");
    assert!(result[2] == "brush teeth" || result[2] == "get dressed");
    assert_eq!(result[3], "go to work");
}
