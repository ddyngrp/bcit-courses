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
	/// Summary description for StepByStep6_23.
	/// </summary>
	public class StepByStep6_23 : System.Windows.Forms.Form
	{
		internal System.Windows.Forms.DataGrid dgCustomers;
		internal System.Windows.Forms.Button btnLoad;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public StepByStep6_23()
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
			this.dgCustomers = new System.Windows.Forms.DataGrid();
			this.btnLoad = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.dgCustomers)).BeginInit();
			this.SuspendLayout();
			// 
			// dgCustomers
			// 
			this.dgCustomers.DataMember = "";
			this.dgCustomers.HeaderForeColor = System.Drawing.SystemColors.ControlText;
			this.dgCustomers.Location = new System.Drawing.Point(8, 40);
			this.dgCustomers.Name = "dgCustomers";
			this.dgCustomers.Size = new System.Drawing.Size(360, 232);
			this.dgCustomers.TabIndex = 3;
			// 
			// btnLoad
			// 
			this.btnLoad.Location = new System.Drawing.Point(8, 8);
			this.btnLoad.Name = "btnLoad";
			this.btnLoad.TabIndex = 2;
			this.btnLoad.Text = "Load Data";
			this.btnLoad.Click += new System.EventHandler(this.btnLoad_Click);
			// 
			// StepByStep6_23
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(376, 285);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.dgCustomers,
																		  this.btnLoad});
			this.Name = "StepByStep6_23";
			this.Text = "StepByStep6_23";
			((System.ComponentModel.ISupportInitialize)(this.dgCustomers)).EndInit();
			this.ResumeLayout(false);

		}
		#endregion
		[STAThread]
		static void Main() 
		{
			Application.Run(new StepByStep6_23());
		}

		private void btnLoad_Click(object sender, System.EventArgs e)
		{
			// Create a SqlConnection
			SqlConnection cnn = new SqlConnection("Data Source=(local);" +
			"Initial Catalog=Northwind;Integrated Security=SSPI");
			// Create a SqlCommand
			SqlCommand cmd = cnn.CreateCommand();
			cmd.CommandType = CommandType.Text;
			cmd.CommandText = "SELECT * FROM Customers";
			// Set up the DataAdapter and fill the DataSet
			SqlDataAdapter da = new SqlDataAdapter();
			da.SelectCommand = cmd;
			DataSet ds = new DataSet();
			da.Fill(ds, "Customers");
			// Create a DataView based on the Customers DataTable
			DataView dv = new DataView(ds.Tables["Customers"]);
			dv.RowFilter = "Country = 'France'";
			dv.Sort = "CompanyName ASC";
			dgCustomers.DataSource = dv;
		}
	}
}
