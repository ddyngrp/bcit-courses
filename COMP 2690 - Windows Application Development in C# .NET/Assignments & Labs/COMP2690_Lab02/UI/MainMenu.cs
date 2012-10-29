using System;

namespace COMP2690_Lab02
{

	public class MainMenu : Menu
	{
		public MainMenu()
		{
			this.title = "Main Menu";

			// Create an array of menu items for this main menu.

			menuItems = new MenuItem[3]; // ERROR: Array was initialized too small.

			menuItems[0] = new MenuItem(new MenuItem.MenuAction(createJob), "Create job");
			menuItems[1] = new MenuItem(new MenuItem.MenuAction(workOnJob), "Work on a job");
			menuItems[2] = new MenuItem(new MenuItem.MenuAction(viewJobsInProgress), "View jobs in progress");
		}

		private void createJob()
		{
			Menu subMenu = new CreateJobMenu();
			subMenu.DoMenu(false);
		}

		private void workOnJob()
		{
			Menu subMenu = new WorkOnJobsMenu();
			subMenu.DoMenu(false);
		}

		private void viewJobsInProgress()
		{
			Console.WriteLine("Jobs in progress\n" + new string('=', 40));
			
			int i;
			VehicleMaintJob job;
			for(i=0; i<incompleteJobs.Count; ++i)
			{
				job = incompleteJobs[i];
				job.PrintReport();
			}
			pause();
		}
			
	}
}
