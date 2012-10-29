using System;

namespace COMP2690_Lab02
{
	public class OilChange : FixedTimeJob
	{
		public OilChange(Vehicle v, Owner o)
			: base(v, o)
		{}

		public override void DoJob()
		{
			int litresOfOil = 0;

			// 4-cylinder engines take 3 litres of oil.
			if(this.Vehicle.Cylinders >= 4)
			{
				litresOfOil = 3;
			}

			// Each additional cylinder takes an additional 1/2 litre.
			litresOfOil += Convert.ToInt32(Math.Ceiling(((this.Vehicle.Cylinders-4) * 0.5)));

            // ERROR: this iterated through the for loop one extra time.
			for (int i = 0; i < litresOfOil; ++i)
			{
				this.parts.Add(new Part("1L Oil", 2.0m));
			}

			// Labour for oil changes is always 0.2 hours.
			labourHours += 0.2f;

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
			return string.Format("Oil Change for {0} on a {1}", Owner, Vehicle);
		}

	}
}
