import lejos.nxt.*;

public class Smell
{
	public static void main(String[] args) throws Exception
	{
		Motor.A.forward();
		Motor.B.forward();
		Thread.sleep(4000);
		Motor.A.stop();
		Motor.B.forward();
		Thread.sleep(850);
		Motor.A.forward();
		Motor.B.forward();
		Thread.sleep(1900);
		Motor.A.backward();
		Motor.B.backward();
		Thread.sleep(3000);
		Motor.A.stop();
		Motor.B.forward();
		Thread.sleep(1600);
		Motor.A.forward();
		Motor.B.forward();
		Thread.sleep(3000);
		
	}
}
