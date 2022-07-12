use rand::prelude::*;
use std::io::Write;

struct Generator<W: Write> {
    rng: ThreadRng,
    length: usize,
	total: usize,
    writer: W,
	values: usize,
	last_value: usize,
}

impl<W: Write> Generator<W> {
    fn new(writer: W, length: usize, depth: usize) -> Generator<W> {
        Generator {
            rng: thread_rng(),
            length,
			total: length.pow((depth + 1) as u32),
            writer,
			values: 0,
			last_value: usize::MAX,
        }
    }

    fn generate_bool(&mut self) {
        write!(self.writer, "{:?}", rand::random::<bool>()).unwrap();
    }

    fn generate_null(&mut self) {
        write!(self.writer, "null").unwrap();
    }

    fn generate_number(&mut self) {
        write!(self.writer, "{}", rand::random::<i64>()).unwrap();
    }

    fn generate_string(&mut self) {
        let s: String = rand::thread_rng()
            .sample_iter(rand::distributions::Alphanumeric)
            .take(20)
            .map(char::from)
            .collect();
        write!(self.writer, "\"{}\"", s).unwrap();
    }

    fn generate_value(&mut self) {
		self.values += 1;
        match self.rng.gen_range(0..4) {
            0 => self.generate_bool(),
            1 => self.generate_null(),
            2 => self.generate_number(),
            3 => self.generate_string(),
            x => panic!("invalid number generated: {}", x),
        }
    }

    fn make_json(&mut self, depth: usize, with_key: bool) {
		if self.values != self.last_value && self.values % (self.total / 10) == 0 {
			log::info!("{}%", 100.0 * ((self.values as f64) / (self.total as f64)));
			self.last_value = self.values;
		}
        for i in 0..self.length {
            if i > 0 {
                write!(self.writer, ",").unwrap();
            }
            if with_key {
                self.generate_string();
                write!(self.writer, ":").unwrap();
            }
            if depth == 0 {
                self.generate_value();
            } else {
                self.generate_nested(depth - 1);
            }
        }
    }

    fn generate_object(&mut self, depth: usize) {
        write!(self.writer, "{{").unwrap();
        self.make_json(depth, true);
        write!(self.writer, "}}").unwrap();
    }

    fn generate_array(&mut self, depth: usize) {
        write!(self.writer, "[").unwrap();
        self.make_json(depth, false);
        write!(self.writer, "]").unwrap();
    }

    fn generate_nested(&mut self, depth: usize) {
        if rand::random() {
            self.generate_object(depth);
        } else {
            self.generate_array(depth);
        }
    }

    fn generate(&mut self, depth: usize) {
        if depth > 0 {
            self.generate_nested(depth);
        } else {
            self.generate_value();
        }
    }
}

pub fn generate<W: Write>(depth: usize, length: usize, writer: W) -> std::io::Result<()> {
    let mut generator = Generator::new(writer, length, depth);
    generator.generate(depth);
	log::info!("100%");
    Ok(())
}
