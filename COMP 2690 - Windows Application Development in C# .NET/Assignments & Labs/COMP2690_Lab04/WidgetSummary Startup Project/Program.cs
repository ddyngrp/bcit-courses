using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace WidgetSummary
{
	class Program
	{
		static void Main(string[] args)
		{
			string dataPath = "..\\..\\Widgets.csv";

			if ( !File.Exists(dataPath) )
			{
				Console.WriteLine("Make sure Widgets.csv is in the project's base path.");
			}
			else
			{
				WidgetCollection widgets = WidgetCollection.CreateFromCSVFile(dataPath);

				if (widgets == null)
				{
					Console.WriteLine("Problem reading file.");
				}
				else
				{
					widgets.PrintSummary();
				}
			}
		}
	}
}
