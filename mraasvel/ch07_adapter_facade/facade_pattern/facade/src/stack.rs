/*
Simplified interface to vector in the form of a stack
*/

pub struct Stack<T> {
    storage: Vec<T>
}

impl <T> Stack<T> {
	pub fn new() -> Stack<T> {
		Stack { storage: Vec::new() }
	}

    pub fn is_empty(&self) -> bool {
        self.storage.is_empty()
    }

    pub fn push(&mut self, value: T) {
        self.storage.push(value)
    }

    pub fn pop(&mut self) -> Option<T> {
        self.storage.pop()
    }

	// return immutable reference to top of stack
	pub fn peek(&self) -> Option<&T> {
		if self.is_empty() {
			None
		} else {
			Some(&self.storage[0])
		}
	}

	pub fn len(&self) -> usize {
		self.storage.len()
	}
}
