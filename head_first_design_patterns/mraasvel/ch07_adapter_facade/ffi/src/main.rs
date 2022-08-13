use std::os::raw::c_int;

#[repr(C)]
#[derive(Debug)]
pub struct CPoint {
    pub x: c_int,
    pub y: c_int,
}

impl From<Vec<i32>> for CPoint {
    fn from(v: Vec<i32>) -> Self {
        assert!(v.len() >= 2);
        CPoint { x: v[0], y: v[1] }
    }
}

#[link(name = "libpoint", kind = "static", path = "./libpoint/")]
extern "C" {
    pub fn add_point(a: CPoint, b: CPoint) -> CPoint;
}

fn main() {
    let a = vec![5, 5];
    let b = vec![42, 42];
    let c = unsafe { add_point(a.into(), b.into()) };

    dbg!(&c);
}
