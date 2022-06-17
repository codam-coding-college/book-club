public abstract class Duck {
	FlyBehavior flyBehavior;
	QuackBehavior quackBehavior;

	public Duck() {}

	public abstract void display();

	public void performFly() {
		flyBehavior.fly();
	}

	public void performQuack() {
		quackBehavior.quack();
	}

	public void swim() {
		System.out.println("All ducks float, even decoys!");
	}

	public void setFlyBehavior(FlyBehavior newBehavior) {
		flyBehavior = newBehavior;
	}

	public void setQuackBehavior(QuackBehavior newBehavior) {
		quackBehavior = newBehavior;
	}
}
