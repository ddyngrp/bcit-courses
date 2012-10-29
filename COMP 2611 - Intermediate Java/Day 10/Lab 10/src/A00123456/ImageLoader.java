package A00123456;

// ImageLoader.java

import java.io.*;
import java.awt.*;
import javax.swing.*;

public class ImageLoader extends JFrame {
	private AnimationLabel label;

	public ImageLoader(int sleepTime) {
		Container contentPane = getContentPane();
		label = new AnimationLabel(sleepTime, "bean");
		contentPane.add(label, BorderLayout.NORTH);

		setSize(500, 320);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		setVisible(true);
		
		label.loadImages();
	}
}