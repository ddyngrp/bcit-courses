package org.trollop.Plot;

import java.util.Random;
import java.util.SortedMap;
import java.util.TreeMap;

import android.app.Activity;
import android.os.Bundle;

public class Plotting extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        //        X-axis Y-axis
        SortedMap<Float, Float> floatPoints = new TreeMap<Float, Float>();
        
//        Random randomGenerator = new Random();
//        for (Float i = 0F; i < 20; i++) {
//        	floatPoints.put(randomGenerator.nextFloat(), randomGenerator.nextFloat());
//        }
        
        Float fl = 0F;
        floatPoints.put(fl++, 0.02F);
        floatPoints.put(fl++, 0.89F);
        floatPoints.put(fl++, 0.70F);
        floatPoints.put(fl++, 0.46F);
        floatPoints.put(fl++, 0.58F);
        floatPoints.put(fl++, 0.67F);
        floatPoints.put(fl++, 0.28F);
        floatPoints.put(fl++, 0.68F);
        floatPoints.put(fl++, 0.84F);
        floatPoints.put(fl++, 0.31F);
        floatPoints.put(fl++, 0.73F);
        floatPoints.put(fl++, 0.64F);
        floatPoints.put(fl++, 0.89F);
        floatPoints.put(fl++, 0.51F);
        floatPoints.put(fl++, 0.47F);
        floatPoints.put(fl++, 0.71F);
        floatPoints.put(fl++, 0.07F);
        floatPoints.put(fl++, 0.15F);
        floatPoints.put(fl++, 0.58F);
        floatPoints.put(fl++, 0.18F);
        
        Chart chart = new Chart(getApplicationContext(),
        		floatPoints,
        		"This is a chart of some sort.",
        		"X Axis",
        		"Y Axis",
        		"X Units",
        		"Y Units",
        		true);
        
        setContentView(chart);
        
        chart.setXDataRange(0F, 3F);
    }
}