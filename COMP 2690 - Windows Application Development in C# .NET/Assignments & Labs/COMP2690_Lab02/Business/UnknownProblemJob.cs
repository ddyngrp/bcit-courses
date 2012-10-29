using System;

namespace COMP2690_Lab02
{
	public class UnknownProblemJob : VehicleMaintJob
	{
		private string problemDescr;

		public UnknownProblemJob(Vehicle v, Owner o, string problemDescr)
			: base(v, o)
		{
			this.problemDescr = problemDescr;
		}

		public void DoSomeOfJob(Parts parts, float labourHours)
		{
			if(parts != null)
			{
				for(int i=0; i<parts.Count; ++i)
				{
					this.parts.Add(parts[i]);
				}
			}

			if(labourHours > 0)
			{
				this.labourHours += labourHours;
			}
		}

		public override void PrintReport()
		{
			Console.WriteLine("Unknown problem job for {0} on a {1}", Owner, Vehicle);
			Console.WriteLine("Problem description: " + problemDescr);
			if(status == Status.Open)
			{
				Console.WriteLine("Hours so far is {0}", labourHours);
			}
			else
			{
				Console.WriteLine("House spent is {0}.  Total cost is {1:C}", labourHours, totalCost);
			}

			Console.WriteLine("    Parts:");
			for(int i=0; i<parts.Count; ++i)
			{
				Console.WriteLine("     {0}, {1:C}", parts[i].Description, parts[i].Cost);
			}
		}

		public override string ToString()
		{
			return string.Format("Unknown problem job for {0} on a {1} ({2})", Owner, Vehicle, problemDescr);
		}
	}

}
