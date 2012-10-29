using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Data.SqlClient;

namespace _316C06
{
	/// <summary>
	/// Summary description for StepByStep6_19.
	/// </summary>
	public class StepByStep6_19 : System.Windows.Forms.Form
	{
		internal System.Windows.Forms.ListBox lbData;
		internal System.Windows.Forms.Button btnLoadData;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public StepByStep6_19()
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
			this.lbData = new System.Windows.Forms.ListBox();
			this.btnLoadData = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// lbData
			// 
			this.lbData.Location = new System.Drawing.Point(8, 48);
			this.lbData.Name = "lbData";
			this.lbData.Size = new System.Drawing.Size(432, 316);
			this.lbData.TabIndex = 3;
			// 
			// btnLoadData
			// 
			this.btnLoadData.Location = new System.Drawing.Point(8, 8);
			this.btnLoadData.Name = "btnLoadData";
			this.btnLoadData.TabIndex = 2;
			this.btnLoadData.Text = "Load Data";
			this.btnLoadData.Click += new System.EventHandler(this.btnLoadData_Click);
			// 
			// StepByStep6_19
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(448, 365);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.lbData,
																		  this.btnLoadData});
			this.Name = "StepByStep6_19";
			this.Text = "StepByStep6_19";
			this.Load += new System.EventHandler(this.StepByStep6_19_Load);
			this.ResumeLayout(false);

		}
		#endregion

		[STAThread]
		static void Main() 
		{
			Application.Run(new StepByStep6_19());
		}

		private void StepByStep6_19_Load(object sender, System.EventArgs e)
		{
		
		}

		private void btnLoadData_Click(object sender, System.EventArgs e)
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
			// Dump the contents of the DataSet

			lbData.Items.Add("DataSet: " + ds.DataSetName);
			foreach (DataTable dt in ds.Tables)
			{
				lbData.Items.Add("  DataTable: " + dt.TableName);
				foreach (DataRow dr in dt.Rows)
				{
					lbData.Items.Add("    DataRow");
					foreach (DataColumn dc in dt.Columns)
					{
					   lbData.Items.Add("      " + dr[dc]);
					}
				}
			}
		}
	}
}
