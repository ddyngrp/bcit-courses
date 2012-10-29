import lejos.nxt.*;

public class OilBarrel
{
	public static void main(String[] args) throws Exception
	{
		Motor.A.forward();
		Motor.B.forward();
		Thread.sleep(5500);
		Motor.A.stop();
		Motor.B.stop();
		Motor.C.setSpeed(300);
		Motor.C.forward();
		Thread.sleep(300);
		Motor.C.stop();
		Thread.sleep(1000);
		Motor.A.backward();
		Motor.B.backward();
		Thread.sleep(5500);
	}
}
