fn main() -> anyhow::Result<()> {
    match std::env::args().skip(1).next() {
        Some(filename) => {
            let file = std::fs::File::open(&filename)?;
            let reader = std::io::BufReader::new(file);
            let result = json_rust::parse(reader)?;
            dbg!(&result);
            Ok(())
        }
        None => {
            anyhow::bail!("usage: a.out FILENAME");
        }
    }
}
