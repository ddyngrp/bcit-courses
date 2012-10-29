using System;

namespace COMP2690_Lab02
{
	public class Vehicle
	{
		private string make;
		private string model;
		private int year;
		private int numCylinders;
		private int displacementCC;
		private float mileageKm;

		/// <summary>
		/// Default constructor.
		/// </summary>
		public Vehicle()
		{
		}

		/// <summary>
		/// Constructor that receives all necessary data to create a Vehicle object.
		/// </summary>
		/// <param name="make">Vehicle's make (e.g. Ford).</param>
		/// <param name="model">Vehicle's model (e.g. Focus).</param>
		/// <param name="year">Vehicle's year of manufacturing (e.g. 2005).</param>
		/// <param name="numCylinders">Number of cylinders this vehicle's engine has.</param>
		/// <param name="displacement">Vehicle's engine displacement in cubic centimetres.</param>
		/// <param name="mileage">Vehicle's current mileage in kilometres.</param>
		public Vehicle
		(
			string make, 
            string model, 
			int year, 
			int numCylinders, 
			int displacementCC, 	// in cc
			float mileageKm 	// in km.
		)
		{
			this.make = make;
			this.model = model;
			this.year = year;
			this.numCylinders = numCylinders;
			this.displacementCC = displacementCC;
			this.mileageKm = mileageKm;
		}

		public string Make 
		{
			get { return make; }
			set { make = value; }
		}

		public string Model
		{
			get { return model; }
			set { model = value; }
		}
	
		public int Year
		{
			get { return year; }
			set { year = value; }
		}

		public int Cylinders
		{
			get { return numCylinders; }
			set { numCylinders = value; }
		}

		public int Displacement
		{
			get { return displacementCC; }
			set { displacementCC = value; }
		}

		public float Mileage
		{
			get { return mileageKm; }
			set { mileageKm = value; }
		}

		public override string ToString()
		{
			return string.Format("{0} {1} {2}", year, make, model);
		}
	}
}
