import lejos.nxt.*;

public class PowerLine 
{
	public static void main(String[] args) throws Exception
	{
		Motor.A.forward();
		Motor.B.forward();
		Thread.sleep(4000);
		Motor.A.backward();
		Motor.B.backward();
		Thread.sleep(4000);
	}
}
