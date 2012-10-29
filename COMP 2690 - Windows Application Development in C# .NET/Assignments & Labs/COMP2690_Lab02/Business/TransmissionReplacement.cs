using System;

namespace COMP2690_Lab02
{
	public class TransmissionReplacement : FixedTimeJob
	{
		public TransmissionReplacement(Vehicle v, Owner o)
			: base(v, o)
		{}

		public override void DoJob()
		{
			labourHours += this.Vehicle.Year >= 1970 ? 3 : 5;

			parts.Add(new Part("Transmission", 500m));
			parts.Add(new Part("Transmission rebuilt kit", 100m));

			base.DoJob();
		}

		public override void PrintReport()
		{
			Console.WriteLine(this);
			base.printReport();
		}
		
		public override string ToString()
		{
			return string.Format("Transmission Replacement for {0} on a {1}", Owner, Vehicle);
		}
	}
}
