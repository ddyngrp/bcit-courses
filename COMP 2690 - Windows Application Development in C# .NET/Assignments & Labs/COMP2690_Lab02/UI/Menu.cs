using System;
using System.Globalization;
using System.Collections;
using System.Diagnostics;

namespace COMP2690_Lab02
{
	public abstract class Menu
	{
		protected const int ABORT_MENU_SELECTION = 99;	// If user enters this number then stop the menu.
		protected string title;
		protected MenuItem [] menuItems;
		protected static VehicleMaintJobs incompleteJobs;
		protected static VehicleMaintJobs completeJobs;

		public Menu() {}

		static Menu()
		{
			incompleteJobs = new VehicleMaintJobs();
			completeJobs = new VehicleMaintJobs();
		}

		public Menu(string title)
		{
			this.title = title;
		}

		public string Title { get { return title; } }

		public int DoMenu(bool selectOnlyNoAction)
		{
			int selection;

			do
			{
				display();
				selection = promptForSelection();

				if (selectOnlyNoAction)
				{
					// No loop, just return selection.
					return selection;
				}
				else if(selection != ABORT_MENU_SELECTION)
				{
					doAction(selection);
				}
			} while(selection != ABORT_MENU_SELECTION);

			return selection;
		}

		protected virtual void display()
		{
			MenuItem item;
			int i;

			ConsoleUtils.Clear();

			Console.WriteLine(title + "\n" + new string('=', 40));
			if (menuItems != null)
			{
				for (i = 0; i < menuItems.Length && menuItems[i] != null; ++i)
				{
					item = menuItems[i];
					Console.WriteLine("{0,2}. {1}", i + 1, item.DisplayName);
				}
			}
			Console.WriteLine("\n{0,2}. {1}", ABORT_MENU_SELECTION, "Exit");
		}

		/// <summary>
		/// This method is virtual so that submenus can handle prompting in
		/// this own way.
		/// </summary>
		/// <returns>1-based menu item selection, or special value to exit 
		/// the menu.</returns>
		protected virtual int promptForSelection()
		{
			string selection;
			bool selectionIsValid = false;

			// Get a menu selection from the user until s/he enters a valid
			// selection.
			do
			{
				Console.Write("\nEnter a selection: ");
				selection = Console.ReadLine();

                // ERROR: we ended up with an infinite loop here as nothing was changing the
                // value of selectionIsValid.
                selectionIsValid = validateSelection(selection);
			} while(!selectionIsValid);

			// Convert from string to integer before returning it.
			return int.Parse(selection);
		}

		protected bool validateSelection(string selection)
		{
			int result;

			if(int.TryParse(selection, NumberStyles.Integer, null, out result))
			{
				if (menuItems == null)
				{
					return (result == ABORT_MENU_SELECTION);
				}
				else if( (result >= 1 && result <= menuItems.Length) || result == ABORT_MENU_SELECTION )
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}

		protected virtual void doAction(int selection)
		{
			Console.WriteLine();
			ConsoleUtils.Clear();
			menuItems[selection-1].DoAction();
		}

		protected virtual void pause()
		{
			Console.WriteLine("\nPress Enter to continue...");
			Console.ReadLine();
		}

		//protected void listIncompleteJobs()
		//{
		//    ConsoleUtils.Clear();
		//    Console.WriteLine("Incomplete Jobs\n" + new string('-', 40));
		//    listJobs(incompleteJobs);
		//}

		protected void listCompleteJobs()
		{
			ConsoleUtils.Clear();
			Console.WriteLine("Complete Jobs\n" + new string('-', 40));
			listJobs(incompleteJobs);
		}

		private void listJobs(VehicleMaintJobs jobs)
		{
			int i;
			VehicleMaintJob job;

			for(i=0; i<jobs.Count; ++i)
			{
				job = jobs[i];
				Console.WriteLine("{0,2}. {1}", i+1, job);
			}

			Console.WriteLine("\n{0,2}. Exit", ABORT_MENU_SELECTION);
		}

		/// <summary>
		/// Prompts for input from the console and converts it to an integer type.
		/// If the input is not an integer then it keeps prompting.
		/// </summary>
		/// <param name="prompt">Message to prompt the user (e.g. "Please enter your age: ")
		/// If this string is null then there is no prompt message.</param>
		/// <returns></returns>
		public static int GetIntegerValue(string prompt)
		{
			// This method is not working correctly.  We'll fix it with
			// the help of Edit and Continue.

			string strInput;
			int intInput;
			bool validInput;

			validInput = false;
			do
			{
				Console.Write(prompt);
				strInput = Console.ReadLine();
				if(int.TryParse(strInput, out intInput))
				{
					validInput = true;
				}
			} while( !validInput );

			return intInput;
		}

		public static int GetIntegerValue(string prompt, int minValue, int maxValue) 
		{
			int input;

			do
			{
				input = GetIntegerValue(prompt);
			} while( input < minValue || input > maxValue );

			return input;
		}
	
		public static int GetIntegerValue(string prompt, int minValue, int maxValue, int specialValue)
		{
			int input;

			do
			{
				input = GetIntegerValue(prompt);
			} while( (input < minValue || input > maxValue) || input != specialValue );

			return input;
		}
	}
}
