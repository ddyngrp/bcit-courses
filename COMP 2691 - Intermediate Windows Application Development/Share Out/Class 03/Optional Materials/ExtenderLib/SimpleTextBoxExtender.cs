using System;
using System.Collections;
using System.ComponentModel;
using System.ComponentModel.Design;
using System.Drawing;
using System.Windows.Forms;
using System.Windows.Forms.Design;


namespace Samples
{
	[ProvideProperty("SelectedBackColor", typeof(TextBox))]
	public class SimpleTextBoxExtender : Component, IExtenderProvider
	{
		public SimpleTextBoxExtender()
		{
			InitializeComponent();

			// Use a hashtable to track selected colors for each
			// extended control
		}


		public bool CanExtend(object target) 
		{
			return (target is TextBox);
		}

		private Color m_SelectedBackColor;
		public Color SelectedBackColor
		{
			get {return m_SelectedBackColor;}
			set {m_SelectedBackColor = value;}
		}


		private Color backupBackColor;
		public Color GetSelectedBackColor(Control control)
		{
			return SelectedBackColor; 
		}
		
		public void SetSelectedBackColor(Control control, Color selColor)
		{
			TextBox t = (TextBox) control;
			SelectedBackColor = selColor;
			t.GotFocus += new EventHandler(TextBox_GotFocus);
			t.LostFocus += new EventHandler(TextBox_LostFocus);
		}


		private void InitializeComponent() 
		{
			SelectedBackColor = Color.Cyan;
		}

		private void TextBox_GotFocus(object sender, EventArgs e)
		{
			TextBox t = (TextBox) sender;
			backupBackColor = t.BackColor;
			t.BackColor = SelectedBackColor;
		}

		private void TextBox_LostFocus(object sender, EventArgs e)
		{
			TextBox t = (TextBox) sender;
			t.BackColor = backupBackColor;
		}
	}
}
