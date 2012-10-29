using System;
using System.Collections.Generic;
using System.Text;

namespace COMP2690_Lab02
{
	/// <summary>
	/// Presents a list of jobs that have no actions associated with them.  Allows
	/// the user to choose a job.
	/// </summary>
	class JobListMenu : Menu
	{
		public JobListMenu(string title, VehicleMaintJobs jobs)
		{
			this.title = title;

			if (jobs != null && jobs.Count > 0)
			{
				menuItems = new MenuItem[jobs.Count];

				for (int i = 0; i < jobs.Count; ++i)
				{
					menuItems[i] = new MenuItem(null, jobs[i].ToString());
				}
			}
		}

	}
}
