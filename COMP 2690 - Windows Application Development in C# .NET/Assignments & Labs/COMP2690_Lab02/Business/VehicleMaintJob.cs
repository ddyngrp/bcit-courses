using System;
using System.Collections;
using System.IO;
using System.Reflection;

namespace COMP2690_Lab02
{
	public abstract class VehicleMaintJob
	{
		public enum Status
		{
			Open,
			Complete
		};

		private Owner owner;
		private Vehicle vehicle;
		protected Status status;
		protected decimal totalCost;
		protected Parts parts;
		protected float labourHours;

		public VehicleMaintJob()
		{
			parts = new Parts();
		}

		public VehicleMaintJob(Vehicle vehicle, Owner owner)
			: this()
		{
			this.owner = owner;
			this.vehicle = vehicle;
			status = Status.Open;
		}


		public decimal GST { get { return 0.07m; } }
		public decimal PST { get { return 0.07m; } }
		public Vehicle Vehicle { get { return vehicle; } }
		public Owner Owner { get { return owner; } }
		public decimal TotalCost { get { return totalCost; } }
		public decimal HourlyRate { get { return 80m; } }

		/// <summary>
		/// Finish the job, setting status to Complete and calculating the total cost.
		/// </summary>
		public virtual void DoJob()
		{
			status = Status.Complete;
			calcTotalCost();
		}

		/// <summary>
		/// This UI-related method shouldn't really be in a business class but for this
		/// assignment, I need some abstract/virtual methods!
		/// </summary>
		public abstract void PrintReport();

		//public abstract bool Save(StreamWriter writer);

		//protected bool commonSaveImplementation(StreamWriter writer)
		//{
		//    vehicle.Save(writer);
		//    owner.Save(writer);
		//    ...
		//}

		protected void printReport()
		{
			if(status == Status.Complete)
			{
				Console.Write("; Total Cost: {0:C}", totalCost);
			}
			Console.WriteLine();
		}

		protected decimal calcTotalCost()
		{
			if(status == Status.Complete)
			{
				// Parts.
				int i;
				for(i=0, totalCost=0; i<parts.Count; ++i)
				{
					totalCost += parts[i].Cost;
				}

				// Labour.
				totalCost += HourlyRate * (decimal)labourHours;

				// Taxes.
				totalCost *= (1.0m + GST + PST);
			}

			return totalCost;
		}
	}

	public class VehicleMaintJobs
	{
		private ArrayList jobs;

		public VehicleMaintJobs()
		{
			jobs = new ArrayList();
		}

		public void Add(VehicleMaintJob job) { jobs.Add(job); }
		public void Remove(VehicleMaintJob job) { jobs.Remove(job); }
		public void RemoteAt(int index) { jobs.RemoveAt(index); }
		public int Count { get { return jobs.Count; } }
		public VehicleMaintJob this[int index] { get { return (VehicleMaintJob)jobs[index]; } }

		//public bool SaveAll(string path)
		//{
		//    StreamWriter writer;

		//    try
		//    {
		//        writer = new StreamWriter(path);

		//        foreach (VehicleMaintJob job in jobs)
		//        {
		//            job.Save(writer);
		//        }

		//        writer.Close();
		//    }
		//    catch (Exception ex)
		//    {
		//        Console.WriteLine(ex.Message);
		//        return false;
		//    }

		//    return true;
		//}

		//public bool LoadAll(string path)
		//{
		//    StreamReader reader;
		//    VehicleMaintJob job;
		//    string jobType;

		//    try
		//    {
		//        reader = new StreamReader(path);

		//        while ( (jobType = reader.ReadLine()) != string.Empty )
		//        {
		//            switch (jobType)
		//            {
		//                case "OilChange":
		//                    jobs.Add(new OilChange(reader));
		//                    break;
		//            }
		//        }

		//        reader.Close();
		//    }
		//    catch (Exception ex)
		//    {
		//        Console.WriteLine(ex.Message);
		//        return false;
		//    }

		//    return true;
		//}
	}

	public abstract class FixedTimeJob : VehicleMaintJob
	{
		public FixedTimeJob(Vehicle v, Owner o)
			: base(v, o)
		{}
	}
}
