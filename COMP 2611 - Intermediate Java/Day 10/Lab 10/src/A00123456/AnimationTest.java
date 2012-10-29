package A00123456;

// Lab10.java

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class AnimationTest {

	private static int sleepTime;

	public static void main(String[] args) {
		if (args.length < 1) {
			sleepTime = 120;
		} else {
			sleepTime = Integer.parseInt(args[0]);
		}
		ImageLoader app = new ImageLoader(sleepTime);
	}
}
