import lejos.nxt.*;

public class SatMission
{
	public static void main(String[] args) throws Exception
	{
		TouchSensor touch = new TouchSensor(SensorPort.S1);

		while(!touch.isPressed())
		{
			Motor.A.forward();
			Motor.B.forward();
		}
		Motor.A.backward();
		Motor.B.backward();
		Thread.sleep(4700);
		Motor.A.stop();
		Thread.sleep(500);
		while(!touch.isPressed())
		{
			Motor.A.forward();
			Motor.B.forward();
		}
		Motor.A.backward();
		Motor.B.backward();
		Thread.sleep(5000);
	}
}
