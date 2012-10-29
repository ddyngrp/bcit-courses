// BounceThread.java

import java.awt.*;
import java.awt.event.*;

import javax.swing.JFrame;

public class BounceThread extends JFrame {
	private Button btnStart = new Button("Start");

	private Button btnClose = new Button("Close");

	private Canvas canvas;

	private Color[] COLORS = { Color.BLACK, Color.BLUE, Color.CYAN,
			Color.DARK_GRAY, Color.GRAY, Color.GREEN, Color.LIGHT_GRAY,
			Color.MAGENTA, Color.ORANGE, Color.PINK, Color.RED, Color.WHITE,
			Color.YELLOW };

	private static int index;

	public BounceThread() {
		super("BounceThread");

		setDefaultCloseOperation(EXIT_ON_CLOSE);
		canvas = new Canvas();
		add(canvas, BorderLayout.CENTER);

		Panel p = new Panel();
		p.add(btnStart);
		p.add(btnClose);
		add(p, BorderLayout.SOUTH);

		btnStart.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (index == COLORS.length) {
					index = 0;
				}
				Ball b = new Ball(canvas, COLORS[index]);
				Bouncer ballThread = new Bouncer(b);
				ballThread.start();
				index++;
			}
		});

		btnClose.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});
	}

	public static void main(String[] args) {
		BounceThread bounceThread = new BounceThread();
		bounceThread.setSize(300, 200);
		bounceThread.setVisible(true);
	}

	class Bouncer extends Thread {

		private Ball ball;

		public Bouncer(Ball ball) {
			this.ball = ball;
		}

		public void run() {
			ball.bounce();
		}

	}
}
