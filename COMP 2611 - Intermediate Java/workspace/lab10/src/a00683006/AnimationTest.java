/**
 * Project: lab10
 * File: delete.java
 * Date: 20-Nov-07
 * Time: 1:21:40 AM
 */
package a00683006;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class AnimationTest {
	private static int sleepTime = 120;

	public static void main(String[] args) {
		if (args.length < 1) {
			sleepTime = 120;

		} else {
			sleepTime = Integer.parseInt(args[0]);
		}

		ImageLoader app = new ImageLoader();
		app.addAnimation(sleepTime, "bean", "NORTH");
		app.addAnimation(sleepTime, "duke", "SOUTH");
	}
}