using System;
using System.Drawing;
using System.Windows.Forms;

namespace asgn5v1
{
	/// <summary>
	/// Summary description for AboutDialogBox.
	/// </summary>
	public class AboutDialogBox: System.Windows.Forms.Form
	{
		public AboutDialogBox()
		{
			//
			// TODO: Add constructor logic here
			//
			Text = "About \"Transformer\"";
			StartPosition = FormStartPosition.CenterParent;
			FormBorderStyle = FormBorderStyle.FixedDialog;
			BackColor = Color.White;
			ControlBox = false;
			MaximizeBox = false;
			MinimizeBox = false;
			ShowInTaskbar = false;
			
			Label label1 = new Label();
			label1.Parent = this;
			label1.Text = "COMP 4560 Transformer Program";
			label1.Font = new Font("Arial",20,
				FontStyle.Bold);
			label1.AutoSize = true;
			label1.TextAlign = ContentAlignment.MiddleCenter;
				
			Label label2 = new Label();
			label2.Parent = this;
			label2.Text = "(DWS, 200810 - Visual Studio 2005 Version";
			label2.Font = new Font("Arial",14,
				FontStyle.Regular);
			label2.AutoSize = true;
			label2.TextAlign = ContentAlignment.MiddleCenter;
			int iClientWidth = Math.Max(label1.Right,label2.Right);
			int currht = label1.Font.Height/2;
			label1.Location = new Point((iClientWidth-label1.Width)/2, currht);
			currht += 3*label1.Font.Height/2;
			label2.Location = new Point((iClientWidth-label2.Width)/2, currht);

			Button button = new Button();
			button.Parent = this;
			button.Text = "OK";
			button.Size = new Size(4*button.Font.Height,
				2*button.Font.Height);
			currht += label2.Font.Height + label1.Font.Height/2;
			button.Location = new Point((iClientWidth-button.Size.Width)/2,	currht);
			button.DialogResult = DialogResult.OK;

			ClientSize = new Size(iClientWidth,button.Bottom+2*button.Font.Height);
		}
	}
}
