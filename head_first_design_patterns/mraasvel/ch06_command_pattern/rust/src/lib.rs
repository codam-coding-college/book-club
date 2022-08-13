mod thread_pool;

use thread_pool::{CommandType, ThreadPool};
struct BasicTask {
	id: u16,
}

impl thread_pool::Command for BasicTask {
	fn execute(&mut self) {
		println!("{} processing some stuff...", self.id);
		std::thread::sleep(std::time::Duration::from_secs(1));
		println!("{} finished processing some stuff...", self.id);
	}
}

fn some_tasks() -> Vec<CommandType> {
	let mut tasks: Vec<CommandType> = Vec::new();
	for id in 0..16 {
		let task = Box::new(BasicTask { id });
		tasks.push(task);
	}
	tasks
}

pub fn run() -> anyhow::Result<()> {
	let num_threads = 4;
	let pool = ThreadPool::new(num_threads)?;
	let tasks = some_tasks();
	for task in tasks {
		pool.push(task);
	}
	Ok(())
}
