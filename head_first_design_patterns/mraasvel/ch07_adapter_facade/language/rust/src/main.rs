struct French {}

impl French {
    fn bonjour(&self) {
        println!("Bonjour!");
    }
}

impl rust::English for French {
    fn hello(&self) {
        self.bonjour();
    }
}

fn main() {
    rust::run(French {});
}
