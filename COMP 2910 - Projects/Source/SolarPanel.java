import lejos.nxt.*;

public class SolarPanel extends Thread {
	public static void main(String[] args) throws Exception {
		// Initiate a new thread
		new SolarPanel().start();
	}
	
	public void run() {
		
		try {
			// Move foward 
			Motor.A.forward();
			Motor.B.forward();
			Thread.sleep(1300);
			Motor.A.stop();
			Motor.B.stop();
			
			// Turn X degrees to the left
			Motor.A.forward();
			Thread.sleep(870);
			
			// Move forward again
			Motor.A.forward();
			Motor.B.forward();
			Thread.sleep(4700);
			Motor.A.stop();
			Motor.B.stop();
			
			// Drop the solar panel
			Motor.C.setSpeed(60);
			Motor.C.rotate(60);
			Thread.sleep(500);
			Motor.C.stop();
			
			// Move backwards
			Motor.A.backward();
			Motor.B.backward();
			Thread.sleep(4700);
			Motor.A.stop();
			Motor.B.stop();
			
			// Raise the arm
			Motor.C.setSpeed(60);
			Motor.C.rotate(-50);
			Motor.C.stop();
			
			// Turn X degrees to the right
			Motor.B.forward();
			Thread.sleep(870);
			
			// Move backwards to base
			Motor.A.backward();
			Motor.B.backward();
			Thread.sleep(1900);
			Motor.A.stop();
			Motor.B.stop();
		}
		catch (Exception e) {
		}
	}
}