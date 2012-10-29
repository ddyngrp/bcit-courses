using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Data.SqlClient;
using System.Xml;

namespace _316C06
{
	/// <summary>
	/// Summary description for GuidedPracticeExercise6_4.
	/// </summary>
	public class GuidedPracticeExercise6_4 : System.Windows.Forms.Form
	{
		internal System.Windows.Forms.Button btnSave;
		internal System.Windows.Forms.DataGrid dgCustomers;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public GuidedPracticeExercise6_4()
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
			this.btnSave = new System.Windows.Forms.Button();
			this.dgCustomers = new System.Windows.Forms.DataGrid();
			((System.ComponentModel.ISupportInitialize)(this.dgCustomers)).BeginInit();
			this.SuspendLayout();
			// 
			// btnSave
			// 
			this.btnSave.Location = new System.Drawing.Point(8, 312);
			this.btnSave.Name = "btnSave";
			this.btnSave.Size = new System.Drawing.Size(112, 23);
			this.btnSave.TabIndex = 3;
			this.btnSave.Text = "Save File";
			this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
			// 
			// dgCustomers
			// 
			this.dgCustomers.CaptionText = "Customers in France";
			this.dgCustomers.DataMember = "";
			this.dgCustomers.HeaderForeColor = System.Drawing.SystemColors.ControlText;
			this.dgCustomers.Location = new System.Drawing.Point(8, 8);
			this.dgCustomers.Name = "dgCustomers";
			this.dgCustomers.Size = new System.Drawing.Size(568, 296);
			this.dgCustomers.TabIndex = 2;
			// 
			// GuidedPracticeExercise6_4
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(584, 341);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.btnSave,
																		  this.dgCustomers});
			this.Name = "GuidedPracticeExercise6_4";
			this.Text = "GuidedPracticeExercise6_4";
			this.Load += new System.EventHandler(this.GuidedPracticeExercise6_4_Load);
			((System.ComponentModel.ISupportInitialize)(this.dgCustomers)).EndInit();
			this.ResumeLayout(false);

		}
		#endregion

		[STAThread]
		static void Main() 
		{
			Application.Run(new GuidedPracticeExercise6_4());
		}

		private void btnSave_Click(object sender, System.EventArgs e)
		{
			// Create an XmlDataDocument from the DataSet
			XmlDataDocument xdd = new XmlDataDocument((DataSet) dgCustomers.DataSource);
			// And save it to a disk file
			XmlTextWriter xtw = new XmlTextWriter(@"c:\temp\FranceCust.xml", System.Text.Encoding.UTF8);
			xdd.WriteTo(xtw);
			xtw.Flush();
			xtw.Close();
			MessageBox.Show(@"Wrote file c:\temp\FranceCust.xml");
		}

		private void GuidedPracticeExercise6_4_Load(object sender, System.EventArgs e)
		{
			// Create a SqlConnection
			SqlConnection cnn = new SqlConnection("Data Source=(local);" +
			"Initial Catalog=Northwind;Integrated Security=SSPI");
			// Create a SqlCommand
			SqlCommand cmd = cnn.CreateCommand();
			cmd.CommandType = CommandType.Text;
			cmd.CommandText = "SELECT * FROM Customers WHERE Country = 'France'";
			// Set up the DataAdapter and fill the DataSet
			SqlDataAdapter da = new SqlDataAdapter();
			da.SelectCommand = cmd;
			DataSet ds = new DataSet();
			da.Fill(ds, "Customers");
			// Show the data on the user interface so the user can edit it
			dgCustomers.DataSource = ds;
			dgCustomers.DataMember = "Customers";
		}
	}
}
