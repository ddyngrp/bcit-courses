using System;

namespace COMP2690_Lab02
{
	public class RadiatorFlush : FixedTimeJob
	{
		public RadiatorFlush(Vehicle v, Owner o)
			: base(v, o)
		{}

		public override void DoJob()
		{
			double dLitresOfCoolant = this.Vehicle.Displacement * 2.5 / 1000;
			int i4LContainersCoolant = ((int)(dLitresOfCoolant/4));

			if( (dLitresOfCoolant/4) > ((int)(dLitresOfCoolant/4)) )
			{
				++i4LContainersCoolant;
			}

			for(int i=0; i<i4LContainersCoolant; ++i)
			{
				this.parts.Add(new Part("4L Coolant", 4.19m));
			}

			// Complete the job.
			base.DoJob();
		}

		public override void PrintReport()
		{
			Console.WriteLine(this);
			base.printReport();
		}

		public override string ToString()
		{
			return string.Format("Radiator Flush for {0} on a {1}", Owner, Vehicle);
		}
	}
}
