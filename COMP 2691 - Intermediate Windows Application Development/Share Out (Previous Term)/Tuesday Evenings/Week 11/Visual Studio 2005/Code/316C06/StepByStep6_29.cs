using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Xml;

namespace _316C06
{
	/// <summary>
	/// Summary description for StepByStep6_29.
	/// </summary>
	public class StepByStep6_29 : System.Windows.Forms.Form
	{
		internal System.Windows.Forms.Button btnModify;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public StepByStep6_29()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.btnModify = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// btnModify
			// 
			this.btnModify.Location = new System.Drawing.Point(72, 24);
			this.btnModify.Name = "btnModify";
			this.btnModify.Size = new System.Drawing.Size(104, 23);
			this.btnModify.TabIndex = 1;
			this.btnModify.Text = "Modify document";
			this.btnModify.Click += new System.EventHandler(this.btnModify_Click);
			// 
			// StepByStep6_29
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(292, 85);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.btnModify});
			this.Name = "StepByStep6_29";
			this.Text = "StepByStep6_29";
			this.Load += new System.EventHandler(this.StepByStep6_29_Load);
			this.ResumeLayout(false);

		}
		#endregion

		[STAThread]
		static void Main() 
		{
			Application.Run(new StepByStep6_29());
		}

		private void StepByStep6_29_Load(object sender, System.EventArgs e)
		{
		
		}

		private void btnModify_Click(object sender, System.EventArgs e)
		{
			// Browse for an XML file
			OpenFileDialog dlgOpen = new OpenFileDialog();
			dlgOpen.Title = "Select a File";
			dlgOpen.Filter = "XML files (*.xml)|*.xml|All Files(*.*)|*.*";
			if(dlgOpen.ShowDialog() == DialogResult.OK)
			{
				// Hook up to the disk file
				XmlTextReader xtr = new XmlTextReader(dlgOpen.FileName);
				xtr.WhitespaceHandling = WhitespaceHandling.None;
				XmlDocument xd = new XmlDocument();
				// Load the file into the XmlDocument
				xd.Load(xtr);
				xtr.Close();
				// Find the root node, and modify it together with its children
				XmlNode xnod = xd.DocumentElement;
				ModifyWithChildren(xnod);
				// Write the modified file to disk
				XmlTextWriter xtw = new XmlTextWriter(dlgOpen.FileName + ".new", System.Text.Encoding.UTF8);
				xd.WriteTo(xtw);
				xtw.Flush();
				xtw.Close();
				MessageBox.Show("Done!");
			}
		}

		private void ModifyWithChildren(XmlNode xnod)
		{
			// Sets all CustomerCity nodes to uppercase
			XmlNode xnodWorking;

			if (xnod.Name == "CustomerCity")
			{
				xnod.FirstChild.Value = xnod.FirstChild.Value.ToUpper();
			}
			// If there are any child nodes, call this procedure recursively
			if (xnod.HasChildNodes)
			{
				xnodWorking = xnod.FirstChild;
				while(xnodWorking != null)
				{
					ModifyWithChildren(xnodWorking);
					xnodWorking = xnodWorking.NextSibling;
				}
			}
		}
	}
}
