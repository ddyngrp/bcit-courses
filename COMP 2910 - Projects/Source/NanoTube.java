import lejos.nxt.*;
public class NanoTube
{
	public static void main(String[] args) throws Exception
	{
		Motor.A.forward();
		Motor.B.forward();
		Thread.sleep(3000);
		Motor.A.backward();
		Motor.B.backward();
		Thread.sleep(3000);
	}
}
