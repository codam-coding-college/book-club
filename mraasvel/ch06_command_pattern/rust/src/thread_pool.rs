use std::thread::{
	JoinHandle,
};
use std::sync::{
	Arc,
	Mutex,
	mpsc::{self, Sender, Receiver},
};

pub trait Command {
	fn execute(&mut self);
}

pub type CommandType = Box<dyn Command + Send>;
type ReceiverType = Arc<Mutex<Receiver<Message>>>;

enum Message {
	Task(CommandType),
	Terminate,
}

struct Worker {
	handle: Option<JoinHandle<()>>
}

impl Worker {
	fn new(receiver: ReceiverType) -> Worker {
		let handle = std::thread::spawn(move || {
			loop {
				// receive message, execute if task, otherwise break
				let message = receiver.lock().unwrap().recv().unwrap();
				match message {
					Message::Task(mut command) => command.execute(),
					Message::Terminate => break,
				}
			}
		});
		Worker {
			handle: Some(handle)
		}
	}
}

impl Drop for Worker {
	fn drop(&mut self) {
		if let Err(e) = self.handle.take().unwrap().join() {
			eprintln!("join error: {:?}", e);
		}
	}
}

pub struct ThreadPool {
	threads: Vec<Worker>,
	sender: Sender<Message>,
}

impl ThreadPool {
	fn init_threads(n: usize, receiver: ReceiverType) -> anyhow::Result<Vec<Worker>> {
		let mut threads = Vec::new();
		for _ in 0..n {
			let worker = Worker::new(Arc::clone(&receiver));
			threads.push(worker);
		}
		Ok(threads)
	}

	pub fn new(n: usize) -> anyhow::Result<ThreadPool> {
		let (sender, receiver) = mpsc::channel();
		let receiver = Arc::new(Mutex::new(receiver));
		let threads = Self::init_threads(n, receiver)?;
		Ok(ThreadPool {
			threads,
			sender,
		})
	}

	pub fn push(&self, task: CommandType) {
		// we could add to a history here if we want to implement undo
		self.sender.send(Message::Task(task)).unwrap();
	}
}

impl Drop for ThreadPool {
	// send termination signal to all threads
	fn drop(&mut self) {
		for _ in 0..self.threads.len() {
			// ignore send failure, it means the threads terminated
			let _ = self.sender.send(Message::Terminate);
		}
	}
}
