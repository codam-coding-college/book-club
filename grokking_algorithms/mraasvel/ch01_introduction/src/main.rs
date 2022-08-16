use std::io::BufRead;

use ch01_introduction::binary_search;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut args = std::env::args();
    let process = args.next().unwrap();
    match (args.next(), args.next()) {
        (Some(file), Some(target)) => {
            let file = std::io::BufReader::new(std::fs::File::open(file)?);
            let mut lines: Vec<_> = file.lines().collect::<Result<Vec<_>, _>>()?;
            lines.sort();
            match binary_search::binary_search(&lines, &target) {
                Some(_) => println!("found: {}", target),
                None => println!("not found: {}", target),
            }
        }
        _ => {
            eprintln!("usage: {} [FILE] [NAME]", process);
            std::process::exit(1);
        }
    }
    Ok(())
}
