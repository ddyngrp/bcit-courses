using System;

namespace COMP2690_Lab02
{
	/// <summary>
	/// Summary description for WorkOnJobsMenu.
	/// </summary>
	public class WorkOnJobsMenu : Menu
	{
		public WorkOnJobsMenu()
		{
			this.title = "Work On Jobs";

			menuItems = new MenuItem[2];
			menuItems[0] = new MenuItem(new MenuItem.MenuAction(workOnAJob), "Work on a job");
			menuItems[1] = new MenuItem(new MenuItem.MenuAction(completeAJob), "Complete a job");
		}

		private void workOnAJob()
		{
			int selection; 
			UnknownProblemJob uprobJob;

			JobListMenu jobListMenu = new JobListMenu("Incomplete Jobs", incompleteJobs);
			selection = jobListMenu.DoMenu(true);
			if (selection != ABORT_MENU_SELECTION)
			{
				uprobJob = incompleteJobs[selection - 1] as UnknownProblemJob;

				if (uprobJob != null)
				{
					Parts parts = null;
					float hours = 0.0f;

					// TODO: Prompt for parts and hours.

					uprobJob.DoSomeOfJob(parts, hours);
				}
				else
				{
					incompleteJobs[selection - 1].DoJob();

					// Move to the "complete" collection.
					completeJobs.Add(incompleteJobs[selection - 1]);
					incompleteJobs.RemoteAt(selection - 1);

					Console.WriteLine("Job is complete!  The total will be: {0:C}", completeJobs[selection - 1].TotalCost);
					pause();
				}
			}
		}

		private void completeAJob()
		{
			int selection; 

			JobListMenu jobListMenu = new JobListMenu("Incomplete Jobs", incompleteJobs);
			selection = jobListMenu.DoMenu(true);

			if(selection != ABORT_MENU_SELECTION)
			{
				incompleteJobs[selection-1].DoJob();

				Console.WriteLine("Job is complete!  The total will be: {0:C}", incompleteJobs[selection-1].TotalCost);

				// Move job to the "complete" collection.
				completeJobs.Add(incompleteJobs[selection-1]);
				incompleteJobs.RemoteAt(selection-1);
				
				pause();
			}
		}


	}
}
