import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;

public class Ball {
	private Canvas box;

	private static final int XSIZE = 10;
	private static final int YSIZE = 10;

	private int x;
	private int y;
	private int dx = 2;
	private int dy = 2;
	private Color color;

	public Ball(Canvas c, Color color) {
		box = c;
		this.color = color;
	}

	public void draw() {
		Graphics g = box.getGraphics();
		g.setColor(color);
		g.fillOval(x, y, XSIZE, YSIZE);
		g.dispose();
	}

	public void move() {
		Graphics g = box.getGraphics();
		Color oldColor = g.getColor();
		g.setXORMode(box.getBackground());
		g.setColor(color);
		g.fillOval(x, y, XSIZE, YSIZE);
		x += dx;
		y += dy;
		Dimension d = box.getSize();
		if (x < 0) {
			x = 0;
			dx = -dx;
		}
		if (x + XSIZE >= d.width) {
			x = d.width - XSIZE;
			dx = -dx;
		}
		if (y < 0) {
			y = 0;
			dy = -dy;
		}
		if (y + YSIZE >= d.height) {
			y = d.height - YSIZE;
			dy = -dy;
		}
		g.fillOval(x, y, XSIZE, YSIZE);
		g.setColor(oldColor);
		g.dispose();
	}

	public void bounce() {
		draw();
		for (;;) {
			move();
			try {
				Thread.sleep(10);
			} catch (InterruptedException e) {
				// We don't care if the thread has been interrupted
			}
		}
	}
}
