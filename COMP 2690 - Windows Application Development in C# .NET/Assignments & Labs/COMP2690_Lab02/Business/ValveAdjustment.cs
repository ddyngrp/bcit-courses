using System;

namespace COMP2690_Lab02
{
	public class ValveAdjustment : FixedTimeJob
	{
		public ValveAdjustment(Vehicle v, Owner o)
			: base(v, o)
		{}

		public override void DoJob()
		{
			parts.Add(new Part("Valve cover gasket", 65m));
			labourHours += (0.15f * this.Vehicle.Cylinders);
			base.DoJob();
		}

		public override void PrintReport()
		{
			Console.WriteLine(this);
			base.printReport();
		}

		public override string ToString()
		{
			return string.Format("Valve Adjustment for {0} on a {1}", Owner, Vehicle);
		}

	}
}
