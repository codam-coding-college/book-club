package com.mycompany.app;

public class CurrentConditionsDisplay implements Display, Observer {
	private float temp;
	private float humidity;
	private float pressure;

	@Override
	public void update(float temp, float humidity, float pressure) {
		this.temp = temp;
		this.humidity = humidity;
		this.pressure = pressure;
		display();
	}

	@Override
	public void display() {
		System.out.println("Current conditions:");
		System.out.println("Temperature: " + temp);
		System.out.println("Humidity: " + humidity);
		System.out.println("Pressure: " + pressure);
	}
}
