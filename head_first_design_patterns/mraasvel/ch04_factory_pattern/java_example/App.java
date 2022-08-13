public class App {
    public static void main(String[] args) {
        PizzaStore store = new NYStylePizzaStore();
        Pizza pizza = store.orderPizza("pepperoni");
    }
}
