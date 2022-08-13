use clap::Parser;

#[derive(Parser, Debug)]
struct Args {
    #[clap(short, long)]
    depth: usize,

    #[clap(short, long)]
    length: usize,
}

// O(length ^ depth)
fn main() -> std::io::Result<()> {
	env_logger::from_env(env_logger::Env::default().default_filter_or("info"))
		.target(env_logger::Target::Stderr)
		.format_timestamp_nanos()
		.init();

    const MAX_VALUES: usize = 10usize.pow(8);
    let Args { depth, length } = Args::parse();
    let total = length.pow((depth + 1).try_into().unwrap());
    if total > MAX_VALUES {
        eprintln!("total values {} exceeds max values {}", total, MAX_VALUES);
        std::process::exit(1);
    }
    json_gen::generate(depth, length, std::io::stdout())?;
    println!("");
    Ok(())
}
