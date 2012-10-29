using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace WidgetSummary
{
	/// <summary>
	/// Represents a collection of Widget objects.  This class is a child
	/// of the generic collection called List<>, which is similar to an
	/// ArrayList but it can only contain Widget objects (forced at the
	/// compiler level) and always returns Widget objects, hence no need to
	/// cast from type Object.  We'll learn more about generics and collection
	/// classes later in the course.
	/// </summary>
	class WidgetCollection : List<Widget>
	{
		/// <summary>
		/// "Factory" method that creates a WidgetCollection object from 
		/// the contents of the specified file.
		/// </summary>
		/// <param name="path">Path and filename of a comma separated value (CSV) file
		/// from which to read data for creating Widget objects.</param>
		/// <returns>A collection of Widget objects.</returns>
		public static WidgetCollection CreateFromCSVFile(string path)
		{
			if (!File.Exists(path)) return null;

			WidgetCollection result = new WidgetCollection();
			StreamReader reader;

			try
			{
				// Open the file.
				reader = new StreamReader(path);

				// For each line from the file, create a Widget object and
				// add it to the result collection.
				string line;
				while ((line = reader.ReadLine()) != null)
				{
					Widget widget = Widget.CreateFromCSV(line);
					if (widget != null)
					{
						// Result is a WidgetCollection object, which has an
						// Add method inherited from List<>.
						result.Add(widget);
					}
				}

				// Don't forget to close the file!
				reader.Close();
			}
			catch (Exception)
			{
				return null;
			}

			return result;
		}

		public void PrintSummary()
		{
            Console.WriteLine("List of all widgets");
            Console.WriteLine("=====================================================================");
            Console.WriteLine("{0,-8} {1,-50} {2,7}", "ID", "Description", "Price");
            Console.WriteLine("---------------------------------------------------------------------");

            foreach (Widget widget in this)
            {
                Console.WriteLine("{0,-8:d6} {1,-50} {2,7:C}", widget.Id, widget.Description, widget.Price);
            }


            Console.ReadLine();
		}
	}
}
