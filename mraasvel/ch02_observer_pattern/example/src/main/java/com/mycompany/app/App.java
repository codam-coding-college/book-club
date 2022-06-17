package com.mycompany.app;

/**
 * Hello world!
 *
 */
public class App 
{
    public static void main( String[] args )
    {
        WeatherData weatherdata = new WeatherData();
        CurrentConditionsDisplay conditions = new CurrentConditionsDisplay();
        weatherdata.registerObserver(conditions);
        weatherdata.setMeasurements(80, 65, 30.4f);
        weatherdata.removeObserver(conditions);
    }
}
