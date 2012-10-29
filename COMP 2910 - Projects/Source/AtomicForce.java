import lejos.nxt.*;

public class AtomicForce extends Thread {
	public static void main(String[] args) throws Exception {
		// Initiate a new thread
		new AtomicForce().start();
	}
	
	public void run() {
		
		try {
			// Move forward
			Motor.A.forward();
			Motor.B.forward();
			Thread.sleep(4500);
			Motor.A.stop();
			Motor.B.stop();

			// Turn X degrees to the right
			Motor.B.forward();
			Thread.sleep(400);
			Motor.B.stop();
			
			// Move the arm up quickly
			Motor.C.setSpeed(40);
			Motor.C.rotate(-60);
			
			// Turn X degrees to the left
			Motor.B.backward();
			Thread.sleep(400);
			Motor.B.stop();
			
			// Move back to the base
			Motor.A.backward();
			Motor.B.backward();
			Thread.sleep(4500);
			Motor.A.stop();
			Motor.B.stop();
		}
		catch (Exception e) {
		}
	}
}