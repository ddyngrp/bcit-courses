using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Data.SqlClient;

namespace _316C06Exercises
{
	/// <summary>
	/// Summary description for Exercise6_1.
	/// </summary>
	public class Exercise6_1 : System.Windows.Forms.Form
	{
		internal System.Windows.Forms.DataGrid dgMain;
		internal System.Windows.Forms.Button btnLoad;
		internal System.Windows.Forms.ComboBox cboCustomers;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public Exercise6_1()
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
			this.dgMain = new System.Windows.Forms.DataGrid();
			this.btnLoad = new System.Windows.Forms.Button();
			this.cboCustomers = new System.Windows.Forms.ComboBox();
			((System.ComponentModel.ISupportInitialize)(this.dgMain)).BeginInit();
			this.SuspendLayout();
			// 
			// dgMain
			// 
			this.dgMain.DataMember = "";
			this.dgMain.HeaderForeColor = System.Drawing.SystemColors.ControlText;
			this.dgMain.Location = new System.Drawing.Point(8, 42);
			this.dgMain.Name = "dgMain";
			this.dgMain.Size = new System.Drawing.Size(528, 328);
			this.dgMain.TabIndex = 5;
			// 
			// btnLoad
			// 
			this.btnLoad.Location = new System.Drawing.Point(288, 10);
			this.btnLoad.Name = "btnLoad";
			this.btnLoad.TabIndex = 4;
			this.btnLoad.Text = "Load Orders";
			this.btnLoad.Click += new System.EventHandler(this.btnLoad_Click);
			// 
			// cboCustomers
			// 
			this.cboCustomers.Location = new System.Drawing.Point(8, 10);
			this.cboCustomers.Name = "cboCustomers";
			this.cboCustomers.Size = new System.Drawing.Size(264, 21);
			this.cboCustomers.TabIndex = 3;
			this.cboCustomers.Text = "ComboBox1";
			// 
			// Exercise6_1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(544, 381);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.dgMain,
																		  this.btnLoad,
																		  this.cboCustomers});
			this.Name = "Exercise6_1";
			this.Text = "Exercise6_1";
			this.Load += new System.EventHandler(this.Exercise6_1_Load);
			((System.ComponentModel.ISupportInitialize)(this.dgMain)).EndInit();
			this.ResumeLayout(false);

		}
		#endregion

		[STAThread]
		static void Main() 
		{
			Application.Run(new Exercise6_1());
		}


		SqlConnection cnn = new SqlConnection("Data Source=(local);" +
		 "Initial Catalog=Northwind;Integrated Security=SSPI");


		private void btnLoad_Click(object sender, System.EventArgs e)
		{
			// Create a new DataSet
			DataSet ds = new DataSet();
			// Load only the customer of interest
			SqlCommand cmdCustomer = cnn.CreateCommand();
			cmdCustomer.CommandType = CommandType.StoredProcedure;
			cmdCustomer.CommandText = "procCustomerDetails";
			cmdCustomer.Parameters.Add(new SqlParameter("@CustomerID", SqlDbType.Text, 5));
			cmdCustomer.Parameters["@CustomerID"].Value = cboCustomers.SelectedValue;
			SqlDataAdapter daCustomer = new SqlDataAdapter();
			daCustomer.SelectCommand = cmdCustomer;
			daCustomer.Fill(ds, "Customers");
			// Load the orders for this customer
			SqlCommand cmdOrders = cnn.CreateCommand();
			cmdOrders.CommandType = CommandType.StoredProcedure;
			cmdOrders.CommandText = "procOrdersForCustomer";
			cmdOrders.Parameters.Add(new SqlParameter("@CustomerID", SqlDbType.Text, 5));
			cmdOrders.Parameters["@CustomerID"].Value = cboCustomers.SelectedValue;
			SqlDataAdapter daOrders = new SqlDataAdapter();
			daOrders.SelectCommand = cmdOrders;
			daOrders.Fill(ds, "Orders");
			// Relate the two DataTables
			DataRelation relCustOrder = ds.Relations.Add("CustOrder", 
			ds.Tables["Customers"].Columns["CustomerID"], 
			ds.Tables["Orders"].Columns["CustomerID"]);
			// Bind the data to the user interface
			dgMain.DataSource = ds;
			dgMain.DataMember = "Customers";
		}

		private void Exercise6_1_Load(object sender, System.EventArgs e)
		{
			// Load the customer list
			SqlCommand cmdCustomers = cnn.CreateCommand();
			cmdCustomers.CommandType = CommandType.StoredProcedure;
			cmdCustomers.CommandText = "procCustomerList";
			cnn.Open();
			DataSet ds = new DataSet();
			SqlDataAdapter da = new SqlDataAdapter();
			da.SelectCommand = cmdCustomers;
			da.Fill(ds, "Customers");
			cboCustomers.DataSource = ds.Tables["Customers"];
			cboCustomers.DisplayMember = "CompanyName";
			cboCustomers.ValueMember = "CustomerID";
			cnn.Close();
		}
	}
}
