use bellman_ford::{Edge, Vertex};

fn main() {
    let graph = vec![
        Vertex {
            id: "S",
            edges: vec![
                Edge {
                    vertex: "A",
                    weight: 10,
                },
                Edge {
                    vertex: "E",
                    weight: 8,
                },
            ],
        },
        Vertex {
            id: "E",
            edges: vec![Edge {
                vertex: "D",
                weight: 1,
            }],
        },
        Vertex {
            id: "A",
            edges: vec![Edge {
                vertex: "C",
                weight: 2,
            }],
        },
        Vertex {
            id: "D",
            edges: vec![
                Edge {
                    vertex: "A",
                    weight: -4,
                },
                Edge {
                    vertex: "C",
                    weight: -1,
                },
            ],
        },
        Vertex {
            id: "C",
            edges: vec![Edge {
                vertex: "B",
                weight: -2,
            }],
        },
        Vertex {
            id: "B",
            edges: vec![Edge {
                vertex: "A",
                weight: 1,
            }],
        },
    ];
    let result = bellman_ford::bellman_ford("S", &graph);
    dbg!(&result);
}
