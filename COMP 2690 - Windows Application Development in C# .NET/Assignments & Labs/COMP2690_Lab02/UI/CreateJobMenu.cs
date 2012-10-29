using System;

namespace COMP2690_Lab02
{
	public class CreateJobMenu : Menu
	{
		public CreateJobMenu()
		{
			this.title = "Create New Job";

			menuItems = new MenuItem[5];
			menuItems[0] = new MenuItem(new MenuItem.MenuAction(createOilChange), "Oil change");
			menuItems[1] = new MenuItem(new MenuItem.MenuAction(createRadFlush), "Radiator flush");
			menuItems[2] = new MenuItem(new MenuItem.MenuAction(createValveAdjustment), "Valve adjustment");
			menuItems[3] = new MenuItem(new MenuItem.MenuAction(createTranmsissionReplacement), "Transmission replacement");
			menuItems[4] = new MenuItem(new MenuItem.MenuAction(createUnknownProblemJob), "Create unknown problem job");
		}

		private Owner getOwnerInfo()
		{
			string input;
			Owner owner = null;
			bool keepPrompting = true;
			
			while(keepPrompting)
			{
				Console.Write("\n(I)ndividual customer or (C)ompany customer: ");
				input = Console.ReadLine();
				if(input.ToUpper() == "I")
				{
					keepPrompting = false;

					owner = new Individual();
					Individual ind = (Individual)owner;

					Console.Write("First name: ");
					ind.FirstName = Console.ReadLine();
					Console.Write("Last name: ");
					ind.LastName = Console.ReadLine();
					Console.Write("Phone number: ");
					ind.PhoneNumber = Console.ReadLine();

				}
				else if(input.ToUpper() == "C")
				{
					keepPrompting = false;

					owner = new Company();
					Company company = (Company)owner;

					Console.Write("Company name: ");
					company.CompanyName = Console.ReadLine();
					Console.Write("Phone number: ");
					company.PhoneNumber = Console.ReadLine();
				}
			}

			return owner;
		}

		private Vehicle getVehicleInfo()
		{
			string make, model;
			int year, numCylinders, displacementCC, mileage;

			Console.Write("\nVehicle make: ");
			make = Console.ReadLine();
			Console.Write("Vehicle model: ");
			model = Console.ReadLine();
			year = GetIntegerValue("Vehicle year: ");
			numCylinders = GetIntegerValue("Vehicle number of cylinders: ");
			displacementCC = GetIntegerValue("Vehicle displacement (in cubic centimetres): ");
			mileage = GetIntegerValue("Vehicle mileage (in kilometres): ");

            // ERROR: was using the default constructor, thereby returning a null object.
			return new Vehicle(make, model, year, numCylinders, displacementCC, mileage);
		}

		private void createOilChange()
		{
			incompleteJobs.Add(new OilChange(getVehicleInfo(), getOwnerInfo()));
		}

		private void createRadFlush()
		{
			incompleteJobs.Add(new RadiatorFlush(getVehicleInfo(), getOwnerInfo()));
		}

		private void createTranmsissionReplacement()
		{
			incompleteJobs.Add(new TransmissionReplacement(getVehicleInfo(), getOwnerInfo()));
		}

		private void createValveAdjustment()
		{
			incompleteJobs.Add(new ValveAdjustment(getVehicleInfo(), getOwnerInfo()));
		}

		private void createUnknownProblemJob()
		{
			Vehicle v = getVehicleInfo();
			Owner o = getOwnerInfo();

			Console.WriteLine("Please describe the problem:");
			string problem = Console.ReadLine();

			incompleteJobs.Add(new UnknownProblemJob(v, o, problem));
		}

	}
}
