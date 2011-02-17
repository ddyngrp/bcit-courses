package org.trollop.Plot;

import java.util.ArrayList;
import java.util.Random;

import android.app.Activity;
import android.os.Bundle;

public class Plotting extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        ArrayList<Object[]> intPoints = new ArrayList<Object[]>();
        
        Random randomGenerator = new Random();
        for (Integer i = 0; i < 20; i++) {
        	Integer randomInt = randomGenerator.nextInt(10);
        	if (i == 1230)
        		randomInt = 0;
        	Object o[] = {i, randomInt};
        	intPoints.add(o);
        }
        
        Chart chart = new Chart(getApplicationContext(),
        		intPoints,
        		"This is a chart of some sort.",
        		"X Axis",
        		"Y Axis",
        		"X Units",
        		"Y Units",
        		false);
        
        setContentView(chart);
    }
}