using System;
using System.Collections;

namespace COMP2690_Lab02
{
	public class Parts
	{
		private ArrayList parts;

		public Parts()
		{
			parts = new ArrayList();
		}

		public Parts(ArrayList parts)
		{
			this.parts = parts;
		}

		public Part this[int index]
		{
			get { return (Part)parts[index]; }
		}

		public void Add(Part p) { parts.Add(p); }
		public void Remove(Part p) { parts.Remove(p); }
		public void RemoveAt(int index) { parts.RemoveAt(index); }
		public int Count { get { return parts.Count; } }
	}



	public class Part
	{
		private string description;
		private decimal cost;

		public Part()
		{
		}

		public Part(string description, decimal cost)
			: this()
		{
			this.description = description;
			this.cost = cost;
		}
	
		public string Description { get { return description; } }
		public decimal Cost { get { return cost; } }

		public override string ToString()
		{
			return string.Format("Description    : {0}\nCost           : {1:C}", description, cost);
		}

	
	}
}
