use eight_puzzle::Board;

mod eight_puzzle;
mod template;

pub fn run() {
    let start = Board::random();
    let goal = Board::goal();
    println!("running astar: {:?} -> {:?}", start, goal);
    match template::astar(start, goal) {
        Some(result) => result.print_history(),
        None => eprintln!("board state not solvable"),
    }
}
