using System;

namespace COMP2690_Lab02
{
	public abstract class Owner
	{
		protected string phoneNumber;

		public Owner()
		{
		}

		public Owner(string phoneNumber)
		{
			this.phoneNumber = phoneNumber;
		}

		public string PhoneNumber 
		{ 
			get { return phoneNumber; } 
			set { phoneNumber = value; }
		}

	}

	public class Individual : Owner
	{
		private string fName, lName;

		public Individual()
		{
		}

		public Individual(string fName, string lName)
			: this()
		{
			this.fName = fName;
			this.lName = lName;
		}

		public string FirstName 
		{
			get { return fName; }
			set { fName = value; }
		}

		public string LastName 
		{
			get { return lName; }
			set { lName = value; }
		}

		public Individual(string fName, string lName, string phoneNumber)
			: base(phoneNumber)
		{
			this.fName = fName;
			this.lName = lName;
		}


		public override string ToString()
		{
			return string.Format("{0}, {1}", lName, fName);
		}
	}

	public class Company : Owner
	{
		private string name;

		public Company()
		{
		}

		public Company(string name)
			: this()
		{
			this.name = name;
		}

		public Company(string name, string phoneNumber)
			: base(phoneNumber)
		{
			this.name = name;
		}

		public string CompanyName 
		{
			get { return name; }
			set { name = value; }
		}


		public override string ToString()
		{
			return name;
		}

	}
}
