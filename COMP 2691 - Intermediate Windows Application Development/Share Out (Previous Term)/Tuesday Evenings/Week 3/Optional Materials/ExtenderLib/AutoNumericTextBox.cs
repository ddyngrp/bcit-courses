using System;
using System.Drawing; 
using System.Windows.Forms;

namespace MsdnMag.ExtenderLib
{
	public class AutoNumericTextBox : AutoColorTextBox
	{
		public AutoNumericTextBox()
		{
			Value = 0.0f;
			NumericMode = false;
			m_oldForeColor = this.ForeColor;
			this.TextAlign = HorizontalAlignment.Right;
			this.LostFocus += new EventHandler(AutoNumericTextBox_LostFocus);
		}

		public double Value;
		private Color m_oldForeColor;
		public bool NumericMode;

		private void AutoNumericTextBox_LostFocus(object sender, EventArgs e)
		{
			if (NumericMode)
			{
				Value = Convert.ToDouble(this.Text);
				if (Value <0)
				{
					this.ForeColor = Color.Red;
					this.Font = new Font(Font.Name, Font.Size, FontStyle.Bold);   
				}
				else
				{
					this.ForeColor = m_oldForeColor;
					this.Font = new Font(Font.Name, Font.Size);   
				}
			}
		}
	}
}
