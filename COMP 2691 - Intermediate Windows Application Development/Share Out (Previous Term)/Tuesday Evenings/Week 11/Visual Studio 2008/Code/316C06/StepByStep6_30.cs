using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Xml;
using System.Data;

namespace _316C06
{
	/// <summary>
	/// Summary description for StepByStep6_30.
	/// </summary>
	public class StepByStep6_30 : System.Windows.Forms.Form
	{
		internal System.Windows.Forms.DataGrid dgXml;
		internal System.Windows.Forms.Button btnLoadXml;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public StepByStep6_30()
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
			this.dgXml = new System.Windows.Forms.DataGrid();
			this.btnLoadXml = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.dgXml)).BeginInit();
			this.SuspendLayout();
			// 
			// dgXml
			// 
			this.dgXml.DataMember = "";
			this.dgXml.HeaderForeColor = System.Drawing.SystemColors.ControlText;
			this.dgXml.Location = new System.Drawing.Point(8, 40);
			this.dgXml.Name = "dgXml";
			this.dgXml.Size = new System.Drawing.Size(520, 304);
			this.dgXml.TabIndex = 3;
			// 
			// btnLoadXml
			// 
			this.btnLoadXml.Location = new System.Drawing.Point(8, 8);
			this.btnLoadXml.Name = "btnLoadXml";
			this.btnLoadXml.TabIndex = 2;
			this.btnLoadXml.Text = "Load XML";
			this.btnLoadXml.Click += new System.EventHandler(this.btnLoadXml_Click);
			// 
			// StepByStep6_30
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(536, 349);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.dgXml,
																		  this.btnLoadXml});
			this.Name = "StepByStep6_30";
			this.Text = "StepByStep6_30";
			((System.ComponentModel.ISupportInitialize)(this.dgXml)).EndInit();
			this.ResumeLayout(false);

		}
		#endregion

		[STAThread]
		static void Main() 
		{
			Application.Run(new StepByStep6_30());
		}

		private void btnLoadXml_Click(object sender, System.EventArgs e)
		{
			// Browse for an XML file
			OpenFileDialog dlgOpen = new OpenFileDialog();
			dlgOpen.Title = "Select a File";
			dlgOpen.Filter = "XML files (*.xml)|*.xml|All Files(*.*)|*.*";
			if (dlgOpen.ShowDialog() == DialogResult.OK)
			{
				// Hook up to the disk file
				XmlTextReader xtr = new XmlTextReader(dlgOpen.FileName);
				XmlDataDocument xdd = new XmlDataDocument();
				// Get the DataSet
				DataSet ds = xdd.DataSet;
				// Read the schema of the file to initialize the DataSet
				ds.ReadXmlSchema(xtr);
				xtr.Close();
				xtr = new XmlTextReader(dlgOpen.FileName);
				xtr.WhitespaceHandling = WhitespaceHandling.None;
				// Load the file into the XmlDataDocument
				xdd.Load(xtr);
				xtr.Close();
				// And display it on the DataGrid
				dgXml.DataSource = ds;
			}
		}
	}
}
