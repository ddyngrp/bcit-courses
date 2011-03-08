/**
 * Project: Assignment_03_2D-Plotting
 * File: Chart.java
 * Date: 2011-02-16
 * Time: 9:09:11 PM
 */
package org.trollop.Plot;

import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;
import java.util.SortedMap;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Paint.Align;
import android.graphics.Paint.Style;
import android.graphics.Path;
import android.graphics.Point;
import android.graphics.PointF;
import android.view.View;

/**
 * Creates a simple scaled line graph with x and y axis labels.
 * 
 * @author Steffen L. Norgren, A00683006
 * 
 */
public class Chart extends View {
	private Paint paint;

	private Point viewSize = new Point();
	private Point margin = new Point(60, 40);
	private PointF minBounds = new PointF(Float.MAX_VALUE, Float.MAX_VALUE);
	private PointF maxBounds = new PointF(Float.MIN_VALUE, Float.MIN_VALUE);
	private PointF xZoomed = new PointF();;

	private boolean smooth;
	private boolean zoomed = false;

	private float chartTitleSize = 18;
	private float axisTitleSize = 14;

	private String chartTitle;
	private String xAxisTitle;
	private String yAxisTitle;
	private String xAxisUnits;
	private String yAxisUnits;

	SortedMap<Float, Float> dataPoints;

	public Chart(Context context, SortedMap<Float, Float> dataPoints,
			String chartTitle, String xAxisTitle, String yAxisTitle,
			String xAxisUnits, String yAxisUnits, boolean smooth) {
		super(context);

		this.paint = new Paint();
		this.chartTitle = chartTitle;
		this.xAxisTitle = xAxisTitle;
		this.yAxisTitle = yAxisTitle;
		this.xAxisUnits = xAxisUnits;
		this.yAxisUnits = yAxisUnits;
		this.dataPoints = dataPoints;
		this.smooth = smooth;
		this.setMinMaxXY();
	}

	@Override
	protected void onDraw(Canvas canvas) {
		viewSize.set(this.getWidth(), this.getHeight());

		drawAxes(canvas);
		plot(canvas);
	}

	private void drawAxes(Canvas canvas) {
		/* Draw x axis */
		paint.setColor(Color.WHITE);
		canvas.drawLine(margin.x, viewSize.y - margin.y, viewSize.x, viewSize.y
				- margin.y, paint);

		/* Draw y axis */
		canvas.drawLine(margin.x, margin.y, margin.x, viewSize.y - margin.y,
				paint);

		/* Draw chart title */
		paint.setColor(Color.YELLOW);
		paint.setTextAlign(Align.CENTER);
		paint.setAntiAlias(true);
		paint.setTextSize(chartTitleSize);
		canvas.drawText(chartTitle, viewSize.x / 2,
				(margin.y + chartTitleSize) / 2, paint);

		/* Draw x axis title */
		paint.setColor(Color.LTGRAY);
		paint.setTextSize(axisTitleSize);

		Path path = new Path();
		path.moveTo(0, viewSize.y);
		path.lineTo(0, 0);

		canvas.drawTextOnPath(xAxisTitle + " (" + xAxisUnits + ") ", path, 0,
				axisTitleSize, paint);

		/* Draw y axis title */
		path.reset();
		path.moveTo(0, viewSize.y);
		path.lineTo(viewSize.x, viewSize.y);

		canvas.drawTextOnPath(yAxisTitle + " (" + yAxisUnits + ") ", path, 0,
				-axisTitleSize / 5, paint);
	}

	public void drawLabels(Canvas canvas) {

	}

	public void setXDataRange(float minX, float maxX) {
		minBounds.set(minX, minBounds.y);
		maxBounds.set(maxX, maxBounds.y);
		this.postInvalidate();
	}

	public void plot(Canvas canvas) {
		boolean initPoint = false;
		int drawWidth = viewSize.x - margin.x;
		int drawHeight = viewSize.y - (margin.y * 2);
		Path path = new Path();

		paint.reset();
		paint.setColor(Color.CYAN);
		paint.setStyle(Style.STROKE);
		paint.setStrokeWidth(1.5F);
		paint.setAntiAlias(true);

		float xMultiplier = drawWidth / (maxBounds.x - minBounds.x);
		float yMultiplier = drawHeight / maxBounds.y;

		// Iterate through the data set
		Set<?> set = dataPoints.entrySet();
		Iterator<?> iterPrev = set.iterator();
		Iterator<?> iterCur = set.iterator();

		if (!smooth) {
			while (iterPrev.hasNext()) {
								
				Map.Entry<?, ?> map = (Entry<?, ?>) iterPrev.next();
				
				if ((Float) map.getKey() >= minBounds.x
						&& (Float) map.getKey() <= maxBounds.x) {
					
					/* set initial point */
					if (!initPoint) {
						path.moveTo((Float) map.getKey(), (Float) map.getValue());
						initPoint = true;
					}

					path.lineTo((Float) map.getKey(), (Float) map.getValue());
				}
			}
		} else {
			iterCur.next(); /* move one point forward */

			while (iterCur.hasNext()) {
				PointF start = new PointF();
				PointF end = new PointF();
				PointF mid = new PointF();

				Map.Entry<?, ?> mapPrev = (Entry<?, ?>) iterPrev.next();
				Map.Entry<?, ?> mapCur = (Entry<?, ?>) iterCur.next();

				if ((Float) mapPrev.getKey() >= minBounds.x
						&& (Float) mapPrev.getKey() <= maxBounds.x) {
					
					/* set initial point */
					if (!initPoint) {
						path.moveTo((Float) mapPrev.getKey(), (Float) mapPrev.getValue());
						initPoint = true;
					}
					
					start.set((Float) mapPrev.getKey(),
							(Float) mapPrev.getValue());

					mid.set(((Float) mapPrev.getKey() + (Float) mapCur.getKey()) / 2,
							((Float) mapPrev.getValue() + (Float) mapCur.getValue()) / 2);

					end.set((Float) mapCur.getKey(), (Float) mapCur.getValue());

					path.quadTo((start.x + mid.x) / 2, start.y, mid.x, mid.y);
					path.quadTo((mid.x + end.x) / 2, end.y, end.x, end.y);
				}
			}
		}

		/* Transformations */
		Matrix m = new Matrix();
		path.offset(-minBounds.x, 0);
		m.setScale(xMultiplier, -yMultiplier);
		path.transform(m);
		path.offset(margin.x + 1, drawHeight + margin.y);
		canvas.drawPath(path, paint);
	}

	private void setMinMaxXY() {
		// Iterate through the data set
		Set<?> set = dataPoints.entrySet();
		Iterator<?> i = set.iterator();

		while (i.hasNext()) {
			Map.Entry<?, ?> map = (Entry<?, ?>) i.next();
			Float yValue = (Float) map.getValue();

			if (yValue < minBounds.y)
				minBounds.set(dataPoints.firstKey(), yValue);
			else if (yValue > maxBounds.y)
				maxBounds.set(dataPoints.lastKey(), yValue);
		}
	}
}