use eight_puzzle::Board;

mod eight_puzzle;
mod template;

pub fn run() -> anyhow::Result<()> {
    let start = Board::random();
    let goal = Board::goal();
    println!("running astar: {:?} -> {:?}", start, goal);
    match template::astar(start, goal) {
        Some(result) => println!("found: {:?}", result),
        None => anyhow::bail!("no goal state found"),
    }
    Ok(())
}
