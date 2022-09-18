use std::collections::HashMap;
use std::iter::FromIterator;

use topological_sort::topological_sort;
use topological_sort::Node;

fn main() {
    let graph = HashMap::from_iter(
        [
            ("a", vec!["b", "c"]),
            ("b", vec!["c"]),
            ("c", vec![]),
            ("d", vec!["a", "b"]),
        ]
        .into_iter()
        .map(|(key, connections)| {
            let node = Node::new(connections.into_iter().map(String::from).collect());
            (key.to_string(), node)
        }),
    );

    let result = topological_sort(&graph);
    dbg!(&result);
    // D is first because it depends on nothing (empty connections)
    // A is second because its only dependency is D
    // B is third because its dependencies (D and A) are before and C is its dependent
    // C is last because it has no dependents, only dependencies
    assert_eq!(result, vec!["d", "a", "b", "c"]);
}
