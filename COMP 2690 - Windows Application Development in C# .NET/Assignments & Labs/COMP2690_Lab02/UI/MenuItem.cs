using System;

namespace COMP2690_Lab02
{
	/// <summary>
	/// Summary description for MenuItem.
	/// </summary>
	public class MenuItem
	{
		// A delegates is a type-safe object-oriented function pointers.  Put 
		// another way, a delegate is a data type that is capable of storing a 
		// reference to a method.
		public delegate void MenuAction();

		protected MenuAction action;
		private string displayName;

		public MenuItem(MenuAction action, string displayName)
		{
			this.action = action;
			this.displayName = displayName;
		}

		public string DisplayName { get { return displayName; } }

		public void DoAction()
		{
			if(action != null) action();
		}


	}
}
