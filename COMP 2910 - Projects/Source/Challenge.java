import lejos.nxt.*;
public class Challenge 
{
	static TouchSensor touch = new TouchSensor(SensorPort.S2);
	public static void main(String[] args) throws Exception
	{
		while(!touch.isPressed())
		{
			Motor.A.forward();
			Motor.B.forward();
		}
		Motor.A.backward();
		Motor.B.backward();
		Thread.sleep(500);
		Motor.A.stop();
		Thread.sleep(1500);
		Motor.A.forward();
		Motor.B.forward();
		Thread.sleep(1000);
	}
}