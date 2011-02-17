/**
 * Project: Assignment_03_2D-Plotting
 * File: Chart.java
 * Date: 2011-02-16
 * Time: 9:09:11 PM
 */
package org.trollop.Plot;

import java.util.ArrayList;

import android.content.Context;
import android.view.View;

/**
 * Creates a simple scaled line graph with x and y axis labels.
 * 
 * @author Steffen L. Norgren, A00683006
 * 
 */
public class Chart extends View {
	
	public Chart(Context context) {
		super(context);
	}

	public void setChartContext(String chartTitle, String xTitle,
			String xUnits, String yTitle, String yUnits, short numXIntersects,
			short numYIntersects) {

	}

	public void setXDataRange(float minX, float maxX) {

	}

	public void setYDataRange(float minY, float maxY) {

	}

	public void setXDataRange(int minX, int maxX) {

	}

	public void setYDataRange(int minY, int maxY) {

	}

	public void plot(ArrayList<?> dataPoints, short xType, short yType,
			boolean smooth) {

	}
	
	
}