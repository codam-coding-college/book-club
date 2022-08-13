public class MallardDuck extends Duck {
	public MallardDuck() {
		flyBehavior = new FlyWithWings();
		quackBehavior = new Quack();
	}

	public void display() {
		System.out.println("This is a Mallard Duck");
	}
}
