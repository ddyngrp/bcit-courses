/**
 * Project: lab10
 * File: delete.java
 * Date: 20-Nov-07
 * Time: 1:21:40 AM
 */
package a00683006;

import java.awt.*;
import javax.swing.*;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class ImageLoader extends JFrame {
	private static final long serialVersionUID = 2178638712638L;
	private AnimationLabel label;

	public ImageLoader() {
		setSize(500, 320);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setVisible(true);
	}
	
	public void addAnimation(int sleepTime, String theme, String layout) {
		Container contentPane = getContentPane();
		
		label = new AnimationLabel(sleepTime, theme);

		if (layout.equalsIgnoreCase("NORTH")) {
			contentPane.add(label, BorderLayout.NORTH);
		}
		else if (layout.equalsIgnoreCase("SOUTH")) {
			contentPane.add(label, BorderLayout.SOUTH);			
		}

		Animation animation = new Animation(label);
		animation.start();
	}
	
	class Animation extends Thread {
		private AnimationLabel label;
		
		public Animation(AnimationLabel label) {
			this.label = label;
		}
		
		public void run() {
			label.loadImages();
		}
	}
}