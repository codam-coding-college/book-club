public class PepperoniPizza extends Pizza {
    public PepperoniPizza() {
        this.name = "pepperoni pizza";
        this.dough = "extra thick dough";
        this.sauce = "bbq sauce";
        this.toppings.add("shredded mozzarella cheese");
    }

    public void prepare() {
        System.out.println("Preparing Pepperoni Pizza");
    }

    public void bake() {
        System.out.println("Baking Pepperoni Pizza");
    }

    public void cut() {
        System.out.println("Cutting Pepperoni Pizza");
    }

    public void box() {
        System.out.println("Boxing Pepperoni Pizza");
    }
}
