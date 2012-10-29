using System;
using System.Collections;
using System.ComponentModel;
using System.ComponentModel.Design;
using System.Drawing;
using System.Windows.Forms;
using System.Windows.Forms.Design;
using System.Reflection;
using System.Runtime.InteropServices;

namespace Samples
{
	[ProvideProperty("BalloonText", typeof(TextBox))]
	public class BalloonToolTip : Component, IExtenderProvider
	{
		private ToolTip _toolTip;
		public BalloonToolTip() 
		{
			_toolTip = new ToolTip();
		}

		// IExtenderProvider::CanExtend
		public bool CanExtend(object extendee) 
		{
			return (extendee is TextBox);
		}	

		// GET--BalloonText
		public string GetBalloonText(Control control)
		{
			return _toolTip.GetToolTip(control); 
		}
		
		// SET--BalloonText
		public void SetBalloonText(Control control, string caption)
		{
			// Change the style if you could do that...
			// TODO

			_toolTip.SetToolTip(control, caption);
		}


	}
}
