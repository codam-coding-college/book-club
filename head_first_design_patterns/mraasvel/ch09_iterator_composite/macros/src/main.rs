#![recursion_limit = "256"]

use std::collections::HashMap;


#[derive(Debug, Clone, PartialEq)]
enum Json {
    Null,
    Boolean(bool),
    Number(f64),
    String(String),
    Array(Vec<Json>),
    Object(Box<HashMap<String, Json>>),
}

macro_rules! json_from_numeric {
    ( $( $T:ty ),* ) => (
        $(
            impl From<$T> for Json {
                fn from(x: $T) -> Self {
                    Json::Number(x as f64)
                }
            }
        )*
    );
}

json_from_numeric!(i8, i16, i32, i64, i128, u8, u16, u32, u64, u128, usize, isize, f32, f64);

impl From<bool> for Json {
    fn from(x: bool) -> Self {
        Json::Boolean(x)
    }
}

impl From<String> for Json {
    fn from(x: String) -> Self {
        Json::String(x)
    }
}

impl <'a> From<&'a str> for Json {
    fn from(x: &'a str) -> Self {
        Json::String(x.to_string())
    }
}

macro_rules! json {
    (null) => ({
        Json::Null
    });
    ( [ $( $x:tt ),* ] ) => ({
        Json::Array( vec![ $( json!($x) ),* ] )
    });
    ( { $( $key:tt : $value:tt ),* } ) => ({
        Json::Object( Box::new(HashMap::from([
            $( ($key.to_string(), json!($value)) ),*
        ])))
    });
    ( $other:tt ) => ({
        Json::from($other)
    });
    ( $x:expr ) => ({
        Json::from($x)
    })
}

fn main() {
    let json = json!({
        "array": ["test", 1, 2],
        "Wow!": "maarten",
        "hello": {
            "key": 03423
        },
        "value": null,
        "true": false
    });
    dbg!(&json);

    if let Json::Object(json) = json {
        match json.get("array").unwrap() {
            Json::Array(arr) => {
                for x in arr {
                    println!("{:?}", x);
                }
            }
            _ => {},
        }
    }

}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn json_null() {
        assert_eq!(json!(null), Json::Null);
    }

    #[test]
    fn json_array() {
        json!([null, null, null]);
    }

    #[test]
    fn json_boolean() {
        assert_eq!(json!(true), Json::Boolean(true));
        assert_eq!(json!(false), Json::Boolean(false));
    }

    #[test]
    fn json_string() {
        assert_eq!(json!("abc".to_string()), Json::String("abc".to_string()));
        assert_eq!(json!("abc"), Json::String("abc".to_string()));
    }

    #[test]
    fn json_numeric() {
        let x = 1.0f64;
        assert_eq!(json!(x), Json::Number(x));
        let x = 10u32;
        assert_eq!(json!(x), Json::Number(x as f64));
        let x = 10i32;
        assert_eq!(json!(x), Json::Number(x as f64));
        let x = 1.0f32;
        assert_eq!(json!(x), Json::Number(x as f64));
        let x = 10usize;
        assert_eq!(json!(x), Json::Number(x as f64));
    }

    #[test]
    fn json_object() {
        let example = Json::Object(
            Box::new(HashMap::from([
                ("name".to_string(), Json::String("maarten".to_string())),
            ]))
        );

        assert_eq!(json!({
            "name": "maarten"
        }), example);
    }


}