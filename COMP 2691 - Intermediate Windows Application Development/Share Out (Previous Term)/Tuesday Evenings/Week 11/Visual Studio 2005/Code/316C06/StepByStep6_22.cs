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
	/// Summary description for StepByStep6_22.
	/// </summary>
	public class StepByStep6_22 : System.Windows.Forms.Form
	{
		internal System.Windows.Forms.ListBox lbSelected;
		internal System.Windows.Forms.Button btnSelect;
		internal System.Windows.Forms.TextBox txtCountry;
		internal System.Windows.Forms.Label Label1;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public StepByStep6_22()
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
			this.lbSelected = new System.Windows.Forms.ListBox();
			this.btnSelect = new System.Windows.Forms.Button();
			this.txtCountry = new System.Windows.Forms.TextBox();
			this.Label1 = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// lbSelected
			// 
			this.lbSelected.Location = new System.Drawing.Point(16, 88);
			this.lbSelected.Name = "lbSelected";
			this.lbSelected.Size = new System.Drawing.Size(296, 316);
			this.lbSelected.TabIndex = 7;
			// 
			// btnSelect
			// 
			this.btnSelect.Location = new System.Drawing.Point(16, 48);
			this.btnSelect.Name = "btnSelect";
			this.btnSelect.TabIndex = 6;
			this.btnSelect.Text = "Select";
			this.btnSelect.Click += new System.EventHandler(this.btnSelect_Click);
			// 
			// txtCountry
			// 
			this.txtCountry.Location = new System.Drawing.Point(184, 8);
			this.txtCountry.Name = "txtCountry";
			this.txtCountry.Size = new System.Drawing.Size(128, 20);
			this.txtCountry.TabIndex = 5;
			this.txtCountry.Text = "";
			// 
			// Label1
			// 
			this.Label1.Location = new System.Drawing.Point(8, 8);
			this.Label1.Name = "Label1";
			this.Label1.Size = new System.Drawing.Size(168, 24);
			this.Label1.TabIndex = 4;
			this.Label1.Text = "Enter a country and click Select";
			// 
			// StepByStep6_22
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(328, 405);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.lbSelected,
																		  this.btnSelect,
																		  this.txtCountry,
																		  this.Label1});
			this.Name = "StepByStep6_22";
			this.Text = "StepByStep6_22";
			this.ResumeLayout(false);

		}
		#endregion

		[STAThread]
		static void Main() 
		{
			Application.Run(new StepByStep6_22());
		}

		private void btnSelect_Click(object sender, System.EventArgs e)
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
			// Use the Select method to get a sorted array of DataRows
			DataRow[] adr = ds.Tables["Customers"].Select( 
			"Country = '" + txtCountry.Text + "'", "ContactName ASC");
			// Dump the result to the user interface
			lbSelected.Items.Clear();
			foreach(DataRow dr in adr)
			{
				lbSelected.Items.Add(dr[0] + " " + dr[1] + " " + dr[2]);
			}
		}

	}
}
