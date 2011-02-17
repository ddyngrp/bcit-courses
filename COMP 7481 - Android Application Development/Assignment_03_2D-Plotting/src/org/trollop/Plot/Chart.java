/**
 * Project: Assignment_03_2D-Plotting
 * File: Chart.java
 * Date: 2011-02-16
 * Time: 9:09:11 PM
 */
package org.trollop.Plot;

import java.util.ArrayList;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Paint.Align;
import android.graphics.Paint.Style;
import android.graphics.Path;
import android.view.View;

/**
 * Creates a simple scaled line graph with x and y axis labels.
 * 
 * @author Steffen L. Norgren, A00683006
 * 
 */
public class Chart extends View {
	private Paint paint;
	
	private int viewXSize;
	private int viewYSize;
	private int xMargin = 60;
	private int yMargin = 40;
	private float chartTitleSize = 18;
	private float axisTitleSize = 15;
	
	private String chartTitle;
	private String xAxisTitle;
	private String yAxisTitle;
	private String xAxisUnits;
	private String yAxisUnits;
	
	ArrayList<Object[]> dataPoints;
	
	public Chart(Context context, ArrayList<Object[]> dataPoints, String chartTitle,
			String xAxisTitle, String yAxisTitle,
			String xAxisUnits, String yAxisUnits, boolean smooth) {
		super(context);
		
		this.paint = new Paint();
		this.chartTitle = chartTitle;
		this.xAxisTitle = xAxisTitle;
		this.yAxisTitle = yAxisTitle;
		this.xAxisUnits = xAxisUnits;
		this.yAxisUnits = yAxisUnits;
		this.dataPoints = dataPoints;
	}
	
	@Override
	protected void onDraw(Canvas canvas) {
		viewXSize = this.getWidth();
		viewYSize = this.getHeight();

		drawAxes(canvas);
		plot(canvas);
	}
	
	private void drawAxes(Canvas canvas) {
		/* Draw x axis */
		paint.setColor(Color.WHITE);
		canvas.drawLine(
				xMargin,
				viewYSize - yMargin,
				viewXSize,
				viewYSize - yMargin,
				paint);
		
		/* Draw y axis */
		canvas.drawLine(
				xMargin,
				yMargin,
				xMargin,
				viewYSize - yMargin,
				paint);
		
		/* Draw chart title */
		paint.setColor(Color.YELLOW);
		paint.setTextAlign(Align.CENTER);
		paint.setAntiAlias(true);
		paint.setTextSize(chartTitleSize);
		canvas.drawText(
				chartTitle,
				viewXSize / 2,
				(yMargin + chartTitleSize) / 2,
				paint);
		
		/* Draw x axis title */
		paint.setColor(Color.LTGRAY);
		paint.setTextSize(axisTitleSize);

		Path path = new Path();
		path.moveTo(0, viewYSize);
		path.lineTo(0, 0);

		canvas.drawTextOnPath(xAxisTitle + " (" + xAxisUnits + ") ",
				path, 0, axisTitleSize, paint);
		
		/* Draw y axis title */
		path.reset();
		path.moveTo(0, viewYSize);
		path.lineTo(viewXSize, viewYSize);

		canvas.drawTextOnPath(yAxisTitle + " (" + yAxisUnits + ") ",
				path, 0, -axisTitleSize / 5, paint);
	}
	
	public void drawLabels(Canvas canvas) {
		
	}
	
	public void setXDataRange(float minX, float maxX) {

	}

	public void setYDataRange(float minY, float maxY) {

	}

	public void setXDataRange(int minX, int maxX) {

	}

	public void setYDataRange(int minY, int maxY) {

	}

	public void plot(Canvas canvas) {
		int drawWidth = viewXSize - xMargin;
		int drawHeight = viewYSize - (yMargin * 2);
		float[] minMaxXY = getMinMaxXY();
		
		/* detect the stored data type and take appropriate action */
		if (!dataPoints.get(0)[1].equals(Integer.TYPE)) {
			paint.reset();
			paint.setColor(Color.CYAN);
			paint.setStyle(Style.STROKE);
			
			float xMultiplier = drawWidth / (minMaxXY[1] - minMaxXY[0]);
			float yMultiplier = drawHeight / minMaxXY[3];
			
			Path path = new Path();
			path.moveTo( /* set initial point */
					(Integer)dataPoints.get(0)[0],
					(Integer)dataPoints.get(0)[1]);
			
			for (int i = 1; i < dataPoints.size(); i++) {
				path.lineTo(
						(Integer)dataPoints.get(i)[0],
						(Integer)dataPoints.get(i)[1]);
			}
			Matrix m = new Matrix();
			m.setScale(xMultiplier, -yMultiplier);
			path.transform(m);
			path.offset(xMargin + 1, drawHeight + yMargin);
			canvas.drawPath(path, paint);
		}
//		else if (dataPoints.get(0)[1].equals(Float.TYPE)) {
//		}
//		else if (dataPoints.get(0)[1].equals(String.class)) {
//		}
	}
	
	private float[] getMinMaxXY() {
		float[] minMaxXY = new float[4];
		
		if (!dataPoints.get(0)[1].equals(Integer.TYPE)) {
			int xSmallest = Integer.MAX_VALUE;
			int xLargest = Integer.MIN_VALUE;
			int ySmallest = Integer.MAX_VALUE;
			int yLargest = Integer.MIN_VALUE;

			for (int i = 0; i < dataPoints.size(); i++) {
				if ((Integer)dataPoints.get(i)[0] < xSmallest)
					xSmallest = (Integer)dataPoints.get(i)[0];
				if ((Integer)dataPoints.get(i)[0] > xLargest)
					xLargest = (Integer)dataPoints.get(i)[0];
				if ((Integer)dataPoints.get(i)[1] < ySmallest)
					ySmallest = (Integer)dataPoints.get(i)[1];
				if ((Integer)dataPoints.get(i)[1] > yLargest)
					yLargest = (Integer)dataPoints.get(i)[1];
			}
			minMaxXY[0] = xSmallest;
			minMaxXY[1] = xLargest;
			minMaxXY[2] = ySmallest;
			minMaxXY[3] = yLargest;
		}
//		else if (dataPoints.get(0)[1].equals(Float.TYPE)) {
//			float xSmallest = Float.MAX_VALUE;
//			float xLargest = Float.MIN_VALUE;
//			float ySmallest = Float.MAX_VALUE;
//			float yLargest = Float.MIN_VALUE;
//
//			for (int i = 0; i < dataPoints.size(); i++) {
//				if ((Float)dataPoints.get(i)[1] < xSmallest)
//					xSmallest = (Float)dataPoints.get(i)[0];
//				if ((Float)dataPoints.get(i)[1] > xLargest)
//					xLargest = (Float)dataPoints.get(i)[0];
//				if ((Float)dataPoints.get(i)[1] < ySmallest)
//					ySmallest = (Float)dataPoints.get(i)[1];
//				if ((Float)dataPoints.get(i)[1] > yLargest)
//					yLargest = (Float)dataPoints.get(i)[1];
//			}
//			minMaxXY[0] = xSmallest;
//			minMaxXY[1] = xLargest;
//			minMaxXY[2] = ySmallest;
//			minMaxXY[3] = yLargest;
//		}
//		else if (dataPoints.get(0)[1].equals(String.class)) {
//			float xSmallest = Float.MAX_VALUE;
//			float xLargest = Float.MIN_VALUE;
//
//			for (int i = 0; i < dataPoints.size(); i++) {
//				if ((Float)dataPoints.get(i)[1] < xSmallest)
//					xSmallest = (Float)dataPoints.get(i)[0];
//				if ((Float)dataPoints.get(i)[1] > xLargest)
//					xLargest = (Float)dataPoints.get(i)[0];
//			}
//			minMaxXY[0] = xSmallest;
//			minMaxXY[1] = xLargest;
//			minMaxXY[2] = Float.MIN_VALUE; /* these will be strings */
//			minMaxXY[3] = Float.MAX_VALUE;
//		}
		
		return minMaxXY;
	}
}