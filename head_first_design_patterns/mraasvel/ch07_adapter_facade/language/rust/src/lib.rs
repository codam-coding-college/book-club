pub trait English {
    fn hello(&self);
}

pub fn run<L: English>(lan: L) {
	lan.hello();
}
