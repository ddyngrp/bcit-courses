using System;
using System.Globalization;

namespace COMP2690_Lab02
{
	class Program
	{
		[STAThread]
		static void Main(string[] args)
		{
			Menu menu = new MainMenu();
			menu.DoMenu(false);
		}
	}
}
