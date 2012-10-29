using System;
using System.Drawing; 
using System.Windows.Forms;

namespace MsdnMag.ExtenderLib
{
	public class AutoColorTextBox : TextBox
	{
		public AutoColorTextBox()
		{
			SelectedBackColor = this.BackColor;
			m_oldBackColor = this.BackColor;
			this.GotFocus += new EventHandler(AutoColorTextBox_GotFocus);
			this.LostFocus += new EventHandler(AutoColorTextBox_LostFocus);
		}

		public Color SelectedBackColor;
		private Color m_oldBackColor;

		private void AutoColorTextBox_GotFocus(object sender, EventArgs e)
		{
			if (this.BackColor != SelectedBackColor)
			{
				m_oldBackColor = this.BackColor;
				this.BackColor = SelectedBackColor;
			}
		}

		private void AutoColorTextBox_LostFocus(object sender, EventArgs e)
		{
			if (m_oldBackColor != this.BackColor)
			{
				this.BackColor = m_oldBackColor;
				m_oldBackColor = this.BackColor;
			}
		}
	}
}
