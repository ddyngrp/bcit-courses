using System;
using System.Collections.Generic;
using System.Text;

namespace WidgetSummary
{
	class Widget
	{
		private int id;
		private string description;
		private decimal price;

		#region "Constructors"

		public Widget(int id, string description, decimal price)
		{
			this.id = id;
			this.description = description;
			this.price = price;
		}

		#endregion

		#region "Property Methods"

        public int Id
        {
            get { return id; }
        }

        public string Description
        {
            get { return description; }
            set { this.description = value; }
        }

        public decimal Price
        {
            get { return price; }
            set { this.price = value; }
        }

		#endregion

		#region "Other Methods"

		public static Widget CreateFromCSV(string csv)
		{
			if (csv == null || csv.Length == 0) return null;

			int tempId;
			string tempDescr;
			decimal tempPrice;

			// Extract the values from csv necessary to create a Widget object.
			//
			// Assumption: csv contains the correct values in the correct order.

			string[] values = csv.Split(',');

			int.TryParse(values[0], out tempId);
			tempDescr = values[1];
			decimal.TryParse(values[2], out tempPrice);

			return new Widget(tempId, tempDescr, tempPrice);
		}

		#endregion
	}
}
