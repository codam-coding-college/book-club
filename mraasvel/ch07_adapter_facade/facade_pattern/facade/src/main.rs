fn main() {
    let mut s = facade::Stack::new();
    s.push(42);
    while !s.is_empty() {
        s.pop();
    }
}
