using System;
using System.Collections;
using System.ComponentModel;
using System.ComponentModel.Design;
using System.Drawing;
using System.Windows.Forms;
using System.Windows.Forms.Design;


namespace Samples
{
	public class TextBoxInfo
	{
		public Color SelectedBackColor;
		public Color OldBackColor;
		public Color SelectedForeColor;
		public Color OldForeColor;
		public bool EventWired;

		public TextBoxInfo()
		{
			SelectedBackColor = Color.Cyan;
			OldBackColor = Color.Empty;
			SelectedForeColor = Color.Black;
			OldForeColor = Color.Empty;
			EventWired = false;
		}
	}

	[ProvideProperty("SelectedBackColor", typeof(TextBox))]
	[ProvideProperty("SelectedForeColor", typeof(TextBox))]
	public class TextBoxExtender : Component, IExtenderProvider
	{
		public TextBoxExtender()
		{
			InitializeComponent();

			// Use a hashtable to track selected colors for each
			// extended control
			this.Extendees = new Hashtable();
		}

		private void InitializeComponent() 
		{
			SelectedBackColor = Color.Cyan;
		}

		// Private table
		private Hashtable Extendees;


		// IExtenderProvider::CanExtend
		public bool CanExtend(object target) 
		{
			return (target is TextBox);
		}

		// SELECTEDBACKCOLOR--Public property for the grid
		private Color m_SelectedBackColor;
		public Color SelectedBackColor
		{
			get {return m_SelectedBackColor;}
			set {m_SelectedBackColor = value;}
		}

		// SELECTEDFORECOLOR--Public property for the grid
		private Color m_SelectedForeColor;
		public Color SelectedForeColor
		{
			get {return m_SelectedForeColor;}
			set {m_SelectedForeColor = value;}
		}


		// GET--SelectedBackColor
		public Color GetSelectedBackColor(Control control)
		{
			// Retrieve related info
			TextBox t = (TextBox) control;
			TextBoxInfo info = (TextBoxInfo) Extendees[t];

			return info.SelectedBackColor; 
		}
		
		// SET--SelectedBackColor
		public void SetSelectedBackColor(Control control, Color selColor)
		{
			TextBoxInfo info; 
			TextBox t = (TextBox) control;
			if (!Extendees.ContainsKey(t))
				info = new TextBoxInfo();
			else
				info = (TextBoxInfo) Extendees[t];
 
			// Store the new value
			info.SelectedBackColor = selColor;

			// If not already done, wire events up
			if (!info.EventWired)
			{
				t.GotFocus += new EventHandler(TextBox_GotFocus);
				t.LostFocus += new EventHandler(TextBox_LostFocus);
				info.EventWired = true;
			}

			// Add to the table
			if (!Extendees.ContainsKey(t))
				Extendees[t] = info;
		}


		// GET--SelectedForeColor
		public Color GetSelectedForeColor(Control control)
		{
			// Retrieve related info
			TextBox t = (TextBox) control;
			TextBoxInfo info = (TextBoxInfo) Extendees[t];

			return info.SelectedForeColor; 
		}
		
		// SET--SelectedForeColor
		public void SetSelectedForeColor(Control control, Color selColor)
		{
			TextBoxInfo info; 
			TextBox t = (TextBox) control;
			if (!Extendees.ContainsKey(t))
				info = new TextBoxInfo();
			else
				info = (TextBoxInfo) Extendees[t];
 
			// Store the new value
			info.SelectedForeColor = selColor;

			// If not already done, wire events up
			if (!info.EventWired)
			{
				t.GotFocus += new EventHandler(TextBox_GotFocus);
				t.LostFocus += new EventHandler(TextBox_LostFocus);
				info.EventWired = true;
			}

			// Add to the table
			if (!Extendees.ContainsKey(t))
				Extendees[t] = info;
		}


		private void TextBox_GotFocus(object sender, EventArgs e)
		{
			// Retrieve related info
			TextBox t = (TextBox) sender;
			TextBoxInfo info = (TextBoxInfo) Extendees[t];

			// Update the info and changes the control's UI
			info.OldBackColor = t.BackColor;
			info.OldForeColor = t.ForeColor;
			t.BackColor = info.SelectedBackColor;
			t.ForeColor = info.SelectedForeColor;
		}

		private void TextBox_LostFocus(object sender, EventArgs e)
		{
			// Retrieve related info
			TextBox t = (TextBox) sender;
			TextBoxInfo info = (TextBoxInfo) Extendees[t];

			// Update the info and changes the control's UI
			t.BackColor = info.OldBackColor;
			info.OldBackColor = Color.Empty;
			t.ForeColor = info.OldForeColor;
			info.OldForeColor = Color.Empty;
		}
	}
}

