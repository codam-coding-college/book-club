use std::collections::HashMap;

pub use dijkstra::solve;

fn main() {
    let graph = HashMap::from([
        ("start", vec![("a", 6), ("b", 2)]),
        ("a", vec![("goal", 1)]),
        ("b", vec![("a", 3), ("goal", 5)]),
    ]);
    let result = solve("start", "goal", &graph);
    dbg!(&result);
}
