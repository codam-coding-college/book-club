package com.mycompany.app;

import java.util.ArrayList;

/**
 * This is a subject class, to which displays can subscribe
 * Inherit from the java 'observable' class
 */
public class WeatherData implements Subject {
	private ArrayList<Observer> observers = new ArrayList<Observer>();
	private float temperature;
	private float humidity;
	private float pressure;

	public void registerObserver(Observer obs) {
		observers.add(obs);
	}

	public void removeObserver(Observer obs) {
		observers.remove(obs);
	}

	public void notifyObservers() {
		for (int i = 0; i < observers.size(); i++) {
			Observer obs = observers.get(i);
			obs.update(getTemperature(), getHumidity(), getPressure());
		}
		System.out.println(computeHeatIndex(temperature, humidity));
	}

	public float getTemperature() {
		return temperature;
	}

	public float getHumidity() {
		return humidity;
	}

	public float getPressure() {
		return pressure;
	}

	public void measurementsChanged() {
		notifyObservers();
	}

	public void setMeasurements(float temp, float humid, float pres) {
		temperature = temp;
		humidity = humid;
		pressure = pres;
		measurementsChanged();
	}

	private float computeHeatIndex(float t, float rh) {
		float index = (float)((16.923 + (0.185212 * t) + (5.37941 * rh) - (0.100254 * t * rh) +
			(0.00941695 * (t * t)) + (0.00728898 * (rh * rh)) +
			(0.000345372 * (t * t * rh)) - (0.000814971 * (t * rh * rh)) +
			(0.0000102102 * (t * t * rh * rh)) - (0.000038646 * (t * t * t)) + (0.0000291583 *  
			(rh * rh * rh)) + (0.00000142721 * (t * t * t * rh)) +
			(0.000000197483 * (t * rh * rh * rh)) - (0.0000000218429 * (t * t * t * rh * rh)) +     
			0.000000000843296 * (t * t * rh * rh * rh)) -
			(0.0000000000481975 * (t * t * t * rh * rh * rh)));
		return index;
	}
}
