import lejos.nxt.*;

public class Damn extends Thread {
	public static void main(String[] args) throws Exception {
		// Initiate a new thread
		new SolarPanel().start();
	}
	
	public void run() {
		
		try {
			// Clamp down on the dam
			Motor.C.setSpeed(60);
			Motor.C.forward();
			Thread.sleep(300);

			// Turn X degrees to the right
			Motor.B.forward();
			Thread.sleep(2000);
			
			// Move forward again
			Motor.A.forward();
			Motor.B.forward();
			Thread.sleep(4700);
			Motor.A.stop();
			Motor.B.stop();
		}
		catch (Exception e) {
		}
	}
}