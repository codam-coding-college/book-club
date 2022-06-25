use std::{fmt::Debug, hash::Hash};

use crate::template::AstarState;

pub struct Board {
    squares: Vec<u8>, // 3x3: 0 represents the empty square
    history: Vec<Board>,
    cost: usize,      // number of moves: g(n)
    score: usize,     // heuristic value: f(n) = h(n) + g(n)
}

impl Clone for Board {
    fn clone(&self) -> Self {
        Board { squares: self.squares.clone(), history: Vec::new(), cost: self.cost, score: self.score }
    }
}

impl Hash for Board {
    fn hash<H: std::hash::Hasher>(&self, state: &mut H) {
        self.squares.hash(state)
    }
}

impl Debug for Board {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "{{ cost: {}, score: {} }}", self.cost, self.score)?;
        for y in 0..3 {
            let row = y * 3;
            writeln!(
                f,
                "{} {} {}",
                self.squares[0 + row],
                self.squares[1 + row],
                self.squares[2 + row]
            )?;
        }
        Ok(())
    }
}

impl Board {
    pub fn new(squares: Vec<u8>, cost: usize) -> Board {
        let score = Board::heuristic(&squares) + cost;
        Board {
            squares,
            cost,
            score,
            history: Vec::new(),
        }
    }

    pub fn random() -> Board {
        use rand::seq::SliceRandom;
        use rand::thread_rng;
        let mut squares: Vec<u8> = (0..9).collect();
        squares.shuffle(&mut thread_rng());
        Board {
            squares,
            cost: 0,
            score: 0,
            history: Vec::new(),
        }
    }

    pub fn goal() -> Board {
        Board {
            squares: (0..9).collect(),
            cost: 0,
            score: 0,
            history: Vec::new(),
        }
    }

    fn heuristic(squares: &[u8]) -> usize {
        #[inline]
        fn position_cost(index: usize, target: usize) -> usize {
            ((index % 3) + index / 3).abs_diff((target % 3) + target / 3)
        }

        squares.into_iter().enumerate().fold(0, |acc, (index, x)| {
            if *x == 0 {
                acc
            } else {
                // x == target index
                // diff(x + y, target_x + target_y) == total moves
                acc + position_cost(index, *x as usize)
            }
        })
    }

    fn empty_square(&self) -> (usize, usize) {
        for y in 0..3 {
            for x in 0..3 {
                if self.squares[y * 3 + x] == 0 {
                    return (x, y);
                }
            }
        }
        panic!("invalid board state");
    }

    fn make_move(&self, (x, y): (usize, usize), (x2, y2): (usize, usize)) -> Board {
        let mut squares = self.squares.clone();
        squares.swap(y * 3 + x, y2 * 3 + x2);
        let mut next = Board::new(squares, self.cost + 1);
        next.history = self.history.clone();
        next.history.push(self.clone());
        next
    }

    pub fn print_history(&self) {
        for x in self.history.iter() {
            println!("{:?}", x);
        }
        println!("{:?}", self);
    }
}

impl AstarState for Board {
    fn expand(&self) -> Vec<Self> {
        let (x, y) = self.empty_square();
        let mut result = Vec::new();
        if y > 0 {
            // up
            result.push(self.make_move((x, y), (x, y - 1)));
        }
        if y < 2 {
            // down
            result.push(self.make_move((x, y), (x, y + 1)));
        }
        if x > 0 {
            // left
            result.push(self.make_move((x, y), (x - 1, y)));
        }
        if x < 2 {
            // right
            result.push(self.make_move((x, y), (x + 1, y)));
        }
        result
    }
}

impl PartialEq for Board {
    fn eq(&self, other: &Self) -> bool {
        // states are equal if their board state is equivalent
        self.squares.eq(&other.squares)
    }
}

impl Eq for Board {}

impl PartialOrd for Board {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(other))
    }
}

impl Ord for Board {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        // compare scores for priority queue
        other.score.cmp(&self.score)
    }
}
