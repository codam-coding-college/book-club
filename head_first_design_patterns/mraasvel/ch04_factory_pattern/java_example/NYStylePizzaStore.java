public class NYStylePizzaStore extends PizzaStore {
    public Pizza createPizza(String type) {
        return new PepperoniPizza();
    }
}
