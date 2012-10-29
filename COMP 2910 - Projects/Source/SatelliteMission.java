import lejos.nxt.*;

public class SatelliteMission
{
	public static void main(String[] args) throws Exception
	{
		//forward and hits the satellite
		Motor.A.forward();
		Motor.B.forward();
		Thread.sleep(5000);
		//backwards towards base
		Motor.A.backward();
		Motor.B.backward();
		Thread.sleep(4000);
		//rotates the robot towards second satellite and goes forward
		Motor.A.stop();
		Thread.sleep(700);
		Motor.A.forward();
		Motor.B.forward();
		Thread.sleep(4000);
		Motor.A.backward();
		Motor.B.backward();
		Thread.sleep(5000);
		Motor.B.rotate(360);
		Motor.A.forward();
		Motor.B.forward();
		Thread.sleep(3000);
	}
}
