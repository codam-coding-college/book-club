use std::{
    collections::HashMap,
    io::{BufRead, Read, Bytes},
};

pub enum JsonNumber {
    Integer(i32),
}

#[derive(Debug)]
pub enum Json {
    Number(i32),
    String(String),
    Object(HashMap<String, Box<Json>>),
    Array(Vec<Box<Json>>),
    Boolean(bool),
    Null,
}

enum State {
	New,
	Object((Json, String)),
	Array(Json),
}

pub struct Parser<R: BufRead> {
    reader: Bytes<R>,
    json: Option<Json>,
	stack: Vec<State>,
}

impl<R: BufRead> Parser<R> {
    pub fn new(reader: R) -> Self {
        Self {
            reader: reader.bytes(),
            json: None,
			stack: Vec::new(),
        }
    }

    pub fn parse(&mut self) -> anyhow::Result<()> {
		self.stack.push(State::New);
		while let Some(top) = self.stack.pop() {
			match top {
				State::New => self.new_state()?,
				State::Object((object, key)) => {
					if let Json::Object(mut object) = object {
						object.insert(key, Box::new(self.json.take().unwrap()));
					} else {
						panic!("expected object state");
					}
				}
				State::Array(array) => {
					if let Json::Array(mut array) = array {
						array.push(Box::new(self.json.take().unwrap()));
					} else {
						panic!("expected array state");
					}
				}
			}
		}
        Ok(())
    }

	fn new_state(&mut self) -> anyhow::Result<()> {
		assert!(self.json.is_none());
		let ch = self.reader.next().ok_or_else(|| anyhow::anyhow!("unexpected eof"))??;
		match ch {
			b'-' | b'0' ..= b'9' => self.parse_number()?,
			b'{' => {}
			b'[' => {}
			b'"' => {}
			b'n' => {}
			b't' | b'f' => {}
			_ => {}
		}
		Ok(())
	}

	fn parse_number(&mut self) -> anyhow::Result<()> {

		Ok(())
	}

    pub fn finish(self) -> Json {
        self.json.expect("finish called on unparsed json parser")
    }
}

pub fn parse<R>(reader: R) -> anyhow::Result<Json>
where
    R: BufRead,
{
    let mut parser = Parser::new(reader);
    parser.parse()?;
    Ok(parser.finish())
}
