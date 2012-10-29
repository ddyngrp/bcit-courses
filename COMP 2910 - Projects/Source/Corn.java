import lejos.nxt.*;

public class Corn
{
	public static void main(String[] args) throws Exception
	{
		Motor.A.forward();
		Motor.B.forward();
		Thread.sleep(240);
		Motor.B.stop();
		Thread.sleep(200);
		Motor.A.forward();
		Motor.B.forward();
		Thread.sleep(3000);
		Motor.A.stop();
		Motor.B.stop();
		Motor.C.setSpeed(300);
		Motor.C.backward();
		Thread.sleep(100);
		Motor.C.stop();
		Thread.sleep(1000);
		Motor.A.backward();
		Motor.B.backward();
		Thread.sleep(3000);
		Motor.B.stop();
		Thread.sleep(1400);
		Motor.A.stop();
		Motor.C.forward();
		Thread.sleep(400);
		Motor.C.stop();
		Motor.A.backward();
		Motor.B.backward();
		Thread.sleep(1000);
		Motor.A.stop();
		Thread.sleep(1100);
		Motor.A.forward();
		Motor.B.forward();
		Thread.sleep(3500);
		Motor.A.stop();
		Motor.B.stop();
		Motor.C.setSpeed(300);
		Motor.C.backward();
		Thread.sleep(100);
		Motor.C.stop();
		Motor.A.forward();
		Thread.sleep(1500);
		Motor.B.forward();
		Thread.sleep(3000);

	}
}
