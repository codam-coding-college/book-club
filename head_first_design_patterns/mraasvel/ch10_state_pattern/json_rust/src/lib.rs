use std::{
    collections::HashMap,
    io::{BufRead, Bytes},
    iter::Peekable,
};

pub enum JsonNumber {
    Integer(i32),
}

#[derive(Debug, PartialEq, Eq)]
pub enum Json {
    Number(i32),
    String(String),
    Object(HashMap<String, Box<Json>>),
    Array(Vec<Box<Json>>),
    Boolean(bool),
    Null,
}

enum State {
    New(u8),
    Object((HashMap<String, Box<Json>>, String)),
    #[allow(clippy::vec_box)]
    Array(Vec<Box<Json>>),
}

pub struct Parser<R: BufRead> {
    reader: Peekable<Bytes<R>>,
    json: Option<Json>,
    byte: u8,
    stack: Vec<State>,
}

impl<R: BufRead> Parser<R> {
    pub fn new(reader: R) -> Self {
        Self {
            reader: reader.bytes().peekable(),
            json: None,
            byte: 0,
            stack: Vec::new(),
        }
    }

    pub fn parse(&mut self) -> anyhow::Result<()> {
        let first = self.next_skip_ws()?;
        self.stack.push(State::New(first));
        while let Some(top) = self.stack.pop() {
            match top {
                State::New(next) => self.new_state(next)?,
                State::Object((object, key)) => {
                    self.parse_object_continued(object, key)?;
                }
                State::Array(array) => {
                    self.parse_array_continued(array)?;
                }
            }
        }
        Ok(())
    }

    fn new_state(&mut self, byte: u8) -> anyhow::Result<()> {
        assert!(self.json.is_none());
        match byte {
            b'-' | b'0'..=b'9' => self.parse_number()?,
            b'n' => self.parse_null()?,
            b't' | b'f' => self.parse_bool()?,
            b'"' => self.parse_string()?,
            b'{' => self.parse_object()?,
            b'[' => self.parse_array()?,
            _ => {}
        }
        Ok(())
    }

    fn parse_number(&mut self) -> anyhow::Result<()> {
        let mut num = String::new();
        num.push(self.byte as char);
        for ch in self.reader.by_ref() {
            let ch = ch?;
            if !ch.is_ascii_digit() {
                break;
            }
            num.push(ch as char);
        }
        self.json = Some(Json::Number(num.parse()?));
        Ok(())
    }

    fn parse_expected(&mut self, expected: &[u8]) -> anyhow::Result<()> {
        for &ch in expected {
            if Some(ch) != self.reader.next().transpose()? {
                anyhow::bail!("expected {ch}");
            }
        }
        Ok(())
    }

    fn parse_null(&mut self) -> anyhow::Result<()> {
        self.parse_expected(b"ull")?;
        self.json = Some(Json::Null);
        Ok(())
    }

    fn parse_bool(&mut self) -> anyhow::Result<()> {
        if self.byte == b't' {
            self.parse_expected(b"rue")?;
            self.json = Some(Json::Boolean(true));
        } else {
            self.parse_expected(b"alse")?;
            self.json = Some(Json::Boolean(false));
        }
        Ok(())
    }

    fn next_escaped_char(&mut self) -> anyhow::Result<u8> {
        let next = self.next()?;
        match next {
            b'"' | b'\\' => Ok(next),
            b'b' => Ok(0x08), // \b
            b'f' => Ok(0x0C), // \f
            b'n' => Ok(b'\n'),
            b'r' => Ok(b'\r'),
            b't' => Ok(b'\t'),
            b'u' => anyhow::bail!("unicode not implemented"),
            ch => anyhow::bail!("unknown escaped character: {ch}"),
        }
    }

    fn parse_string(&mut self) -> anyhow::Result<()> {
        let mut result = Vec::new();
        while let Some(ch) = self.reader.next() {
            let ch = ch?;
            match ch {
                b'"' => break,
                b'\\' => result.push(self.next_escaped_char()?),
                ch => result.push(ch),
            }
        }
        self.json = Some(Json::String(String::from_utf8(result)?));
        Ok(())
    }

    fn parse_object(&mut self) -> anyhow::Result<()> {
        let object = HashMap::new();
        let next = self.next_skip_ws()?;
        match next {
            b'"' => {
                self.parse_object_key(object)?;
            }
            b'}' => {
                self.json = Some(Json::Object(object));
            }
            _ => {
                anyhow::bail!("unexpected character while parsing object: {next}");
            }
        }
        Ok(())
    }

    fn parse_object_key(&mut self, object: HashMap<String, Box<Json>>) -> anyhow::Result<()> {
        self.parse_string()?;
        if let Json::String(key) = self.json.take().unwrap() {
            let next = self.next_skip_ws()?;
            if next != b':' {
                anyhow::bail!("expected ':', found: {next}");
            }

            self.stack.push(State::Object((object, key)));
            let next = self.next_skip_ws()?;
            self.stack.push(State::New(next));
        } else {
            panic!("expected string object on self.json");
        }
        Ok(())
    }

    fn parse_object_continued(
        &mut self,
        mut object: HashMap<String, Box<Json>>,
        key: String,
    ) -> anyhow::Result<()> {
        object.insert(key, Box::new(self.json.take().unwrap()));
        let next = self.next_skip_ws()?;
        match next {
            b',' => {
                let next = self.next_skip_ws()?;
                if next != b'"' {
                    anyhow::bail!("expected '\"' for object key, found: {next}");
                }
                self.parse_object_key(object)?;
            }
            b'}' => {
                self.json = Some(Json::Object(object));
            }
            _ => anyhow::bail!("unexpected character: {next}, expected ',' or '}}'"),
        }
        Ok(())
    }

    fn parse_array(&mut self) -> anyhow::Result<()> {
        let array = Vec::new();
        match self.next_skip_ws()? {
            b']' => self.json = Some(Json::Array(array)),
            byte => {
                self.stack.push(State::Array(array));
                self.stack.push(State::New(byte));
            }
        }
        Ok(())
    }

    #[allow(clippy::vec_box)]
    fn parse_array_continued(&mut self, mut array: Vec<Box<Json>>) -> anyhow::Result<()> {
        array.push(Box::new(self.json.take().unwrap()));
        match self.next_skip_ws()? {
            b']' => self.json = Some(Json::Array(array)),
            b',' => {
                self.stack.push(State::Array(array));
                let next = self.next_skip_ws()?;
                self.stack.push(State::New(next));
            }
            next => anyhow::bail!("unexpected character while parsing array: {next}"),
        }
        Ok(())
    }

    fn next(&mut self) -> anyhow::Result<u8> {
        self.byte = self
            .reader
            .next()
            .ok_or_else(|| anyhow::anyhow!("unexpected eof"))??;
        Ok(self.byte)
    }

    fn next_skip_ws(&mut self) -> anyhow::Result<u8> {
        self.byte = self
            .reader
            .by_ref()
            .find(|ch| {
                ch.as_ref()
                    .map(|b| !b.is_ascii_whitespace())
                    .unwrap_or(false)
            })
            .ok_or_else(|| anyhow::anyhow!("unexpected eof"))??;
        Ok(self.byte)
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

#[test]
fn test_null() {
    let input = "null";
    let reader = std::io::BufReader::new(std::io::Cursor::new(input));
    let result = parse(reader).unwrap();
    assert_eq!(result, Json::Null);
}

#[test]
fn test_true() {
    let input = "true";
    let reader = std::io::BufReader::new(std::io::Cursor::new(input));
    let result = parse(reader).unwrap();
    assert_eq!(result, Json::Boolean(true));
}

#[test]
fn test_false() {
    let input = "false";
    let reader = std::io::BufReader::new(std::io::Cursor::new(input));
    let result = parse(reader).unwrap();
    assert_eq!(result, Json::Boolean(false));
}
#[test]
fn test_number() {
    let input = "-123457";
    let reader = std::io::BufReader::new(std::io::Cursor::new(input));
    let result = parse(reader).unwrap();
    assert_eq!(result, Json::Number(-123457));
}

#[test]
fn test_string() {
    let input = "\"Hello, World!\"";
    let reader = std::io::BufReader::new(std::io::Cursor::new(input));
    let result = parse(reader).unwrap();
    assert_eq!(result, Json::String("Hello, World!".into()));
}

#[test]
fn test_object() {
    let input = "
	{
		\"Key\": \"Value\",
		\"KeyTwo\": 1234
	}
	";
    let reader = std::io::BufReader::new(std::io::Cursor::new(input));
    let result = parse(reader).unwrap();
    assert_eq!(
        result,
        Json::Object(HashMap::from_iter(
            [
                (
                    "Key".to_string(),
                    Box::new(Json::String("Value".to_string()))
                ),
                ("KeyTwo".to_string(), Box::new(Json::Number(1234)))
            ]
            .into_iter()
        ))
    );
}

#[test]
fn test_array() {
    let input = "
	[
		\"Value\",
		1234
	]
	";
    let reader = std::io::BufReader::new(std::io::Cursor::new(input));
    let result = parse(reader).unwrap();
    assert_eq!(
        result,
        Json::Array(vec![
            Box::new(Json::String("Value".to_string())),
            Box::new(Json::Number(1234)),
        ])
    );
}
