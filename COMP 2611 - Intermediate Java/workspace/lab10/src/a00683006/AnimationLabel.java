/**
 * Project: lab10
 * File: delete.java
 * Date: 20-Nov-07
 * Time: 1:21:40 AM
 */
package a00683006;

import javax.swing.*;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class AnimationLabel extends JLabel {
	private static final long serialVersionUID = 62718736L;
	private static final int MAX_IMAGE = 10;
	private String theme;
	private int sleepTime;
	private int current = 0;
	private ImageIcon[] pict = new ImageIcon[MAX_IMAGE];

	public AnimationLabel(int sleepTime, String theme) {
		this.sleepTime = sleepTime;
		this.theme = theme;

		setHorizontalAlignment(SwingConstants.CENTER);

		for (int i = 0; i < MAX_IMAGE; i++) {
			String file = "images/" + theme + "/" + theme + (i + 1) + ".gif";
			pict[i] = new ImageIcon(file);
		}
	}

	public void loadImages() {
		while (true) {
			setIcon(pict[current]);
			current++;

			if (current == MAX_IMAGE)
				current = 0;
			try {
				Thread.sleep(sleepTime);
			} catch (InterruptedException e) {
			}
		}
	}
}