import lejos.nxt.*;
public class  Wave
{
	public static void main(String[] args) throws Exception
	{
		// Move forward until just past the bone
		Motor.A.forward();
		Motor.B.forward();
		Thread.sleep(5000);
		Motor.A.stop();
		Motor.B.stop();
		
		// Turn right X degrees
		Motor.A.forward();
		Thread.sleep(300);
		Motor.A.stop();
		
		// Move forward
		Motor.A.forward();
		Motor.B.forward();
		Thread.sleep(2000);
		Motor.A.stop();
		Motor.B.stop();
		
		// Turn left X degrees
		Motor.B.forward();
		Thread.sleep(200);
		Motor.B.stop();
		
		// Move forward to the wave machine	
		Motor.A.forward();
		Motor.B.forward();
		Thread.sleep(3000);
		Motor.A.stop();
		Motor.B.stop();
		
		// Rotate the robot to activate the wave machine
		Motor.B.forward();
		Motor.A.backward();
		Thread.sleep(1100);
		Motor.B.stop();
		Motor.A.stop();
		
		// Move forward again
		Motor.A.forward();
		Motor.B.forward();
		Thread.sleep(1500);
		Motor.A.stop();
		Motor.B.stop();
		
		// Turn left to avoid the bone
		Motor.A.forward();
		Thread.sleep(300);
		Motor.A.stop();
		
		// Continue moving forward to base
		Motor.A.forward();
		Motor.B.forward();
		Thread.sleep(9000);
	}
}
