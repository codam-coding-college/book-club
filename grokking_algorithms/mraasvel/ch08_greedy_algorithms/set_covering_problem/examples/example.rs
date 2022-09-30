use std::collections::HashSet;

use set_covering_problem::{greedy_set_covering_problem, RadioStation};

fn main() {
    let stations = vec![
        RadioStation {
            id: "kone",
            states: HashSet::from(["id", "nv", "ut"]),
        },
        RadioStation {
            id: "ktwo",
            states: HashSet::from(["wa", "id", "mt"]),
        },
        RadioStation {
            id: "kthree",
            states: HashSet::from(["or", "nv", "ca"]),
        },
        RadioStation {
            id: "kfour",
            states: HashSet::from(["nv", "ut"]),
        },
        RadioStation {
            id: "kfive",
            states: HashSet::from(["ca", "az"]),
        },
    ];
    let states_needed = HashSet::from(["mt", "wa", "or", "id", "nv", "ut", "ca", "az"]);
    let result = greedy_set_covering_problem(&states_needed, stations);
    dbg!(&result);
}
