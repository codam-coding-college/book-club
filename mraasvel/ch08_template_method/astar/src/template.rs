use std::{
    collections::{BinaryHeap, HashSet},
    hash::Hash,
};

pub trait AstarState: Sized {
    fn expand(&self) -> Vec<Self>;
}

/// Takes a start and goal state
/// Returns the expanded goal state if reached
pub fn astar<S>(start: S, goal: S) -> Option<S>
where
    S: AstarState + Ord + Eq + Clone + Hash,
{
    // priority queue: max heap, meaning largest value == highest priority
    let mut pq = BinaryHeap::new();
    let mut visited = HashSet::new();
    let mut iterations = 0;
    pq.push(start);
    while !pq.is_empty() {
        let top = pq.pop().unwrap();
        // goal state comparison
        if top == goal {
            return Some(top);
        }
        // state expansion: also includes heuristic calculation
        let states = top.expand();
        for state in states {
            // skip nodes already visited
            if !visited.contains(&state) {
                visited.insert(state.clone());
                pq.push(state);
            }
        }
        iterations += 1;
    }
    println!("no goal state in {} iterations", iterations);
    None
}
