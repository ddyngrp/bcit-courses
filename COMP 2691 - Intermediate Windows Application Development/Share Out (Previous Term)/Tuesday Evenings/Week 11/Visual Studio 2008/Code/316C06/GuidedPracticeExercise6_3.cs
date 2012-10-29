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
	/// Summary description for GuidedPracticeExercise6_3.
	/// </summary>
	public class GuidedPracticeExercise6_3 : System.Windows.Forms.Form
	{
		internal System.Windows.Forms.DataGrid dgOrders;
		internal System.Windows.Forms.ComboBox cboCustomers;
		internal System.Windows.Forms.Label Label1;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public GuidedPracticeExercise6_3()
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
			this.dgOrders = new System.Windows.Forms.DataGrid();
			this.cboCustomers = new System.Windows.Forms.ComboBox();
			this.Label1 = new System.Windows.Forms.Label();
			((System.ComponentModel.ISupportInitialize)(this.dgOrders)).BeginInit();
			this.SuspendLayout();
			// 
			// dgOrders
			// 
			this.dgOrders.DataMember = "";
			this.dgOrders.HeaderForeColor = System.Drawing.SystemColors.ControlText;
			this.dgOrders.Location = new System.Drawing.Point(16, 40);
			this.dgOrders.Name = "dgOrders";
			this.dgOrders.Size = new System.Drawing.Size(416, 296);
			this.dgOrders.TabIndex = 5;
			// 
			// cboCustomers
			// 
			this.cboCustomers.Location = new System.Drawing.Point(224, 8);
			this.cboCustomers.Name = "cboCustomers";
			this.cboCustomers.Size = new System.Drawing.Size(208, 21);
			this.cboCustomers.TabIndex = 4;
			this.cboCustomers.Text = "ComboBox1";
			this.cboCustomers.SelectedIndexChanged += new System.EventHandler(this.cboCustomers_SelectedIndexChanged);
			// 
			// Label1
			// 
			this.Label1.Location = new System.Drawing.Point(8, 8);
			this.Label1.Name = "Label1";
			this.Label1.Size = new System.Drawing.Size(200, 16);
			this.Label1.TabIndex = 3;
			this.Label1.Text = "Select a customer to see their orders";
			// 
			// GuidedPracticeExercise6_3
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(440, 341);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.dgOrders,
																		  this.cboCustomers,
																		  this.Label1});
			this.Name = "GuidedPracticeExercise6_3";
			this.Text = "GuidedPracticeExercise6_3";
			this.Load += new System.EventHandler(this.GuidedPracticeExercise6_3_Load);
			((System.ComponentModel.ISupportInitialize)(this.dgOrders)).EndInit();
			this.ResumeLayout(false);

		}
		#endregion

        [STAThread]
		static void Main() 
		{
			Application.Run(new GuidedPracticeExercise6_3());
		}

		// Create a SqlConnection
		SqlConnection cnn = new SqlConnection("Data Source=(local);" +
        "Initial Catalog=Northwind;Integrated Security=SSPI");
		// DataSet to hold order information
		DataSet dsOrders = new DataSet();

		private void GuidedPracticeExercise6_3_Load(object sender, System.EventArgs e)
		{
			// Get all of the orders
			SqlCommand cmdOrders = cnn.CreateCommand();
			cmdOrders.CommandType = CommandType.Text;
			cmdOrders.CommandText = "SELECT * FROM Orders";
			SqlDataAdapter daOrders = new SqlDataAdapter();
			daOrders.SelectCommand = cmdOrders;
			daOrders.Fill(dsOrders, "Orders");
			// Retrieve data for the combo box
			SqlCommand cmdCustomers = cnn.CreateCommand();
			cmdCustomers.CommandType = CommandType.Text;
			cmdCustomers.CommandText = "SELECT CustomerID, CompanyName " +
			"FROM Customers ORDER BY CompanyName";
			DataSet ds = new DataSet();
			SqlDataAdapter da = new SqlDataAdapter();
			da.SelectCommand = cmdCustomers;
			da.Fill(ds, "Customers");
			cboCustomers.DisplayMember = "CompanyName";
			cboCustomers.ValueMember = "CustomerID";
			cboCustomers.DataSource = ds.Tables["Customers"];
		}

		private void cboCustomers_SelectedIndexChanged(object sender, System.EventArgs e)
		{
			// Create a DataView containing the orders for the selected customer
			DataView dv = new DataView(dsOrders.Tables["Orders"]);
			dv.RowFilter = "CustomerID = '" + cboCustomers.SelectedValue + "'";
			dgOrders.DataSource = dv;
		}
	}
}
