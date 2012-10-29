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
	/// Summary description for StepByStep6_21.
	/// </summary>
	public class StepByStep6_21 : System.Windows.Forms.Form
	{
		internal System.Windows.Forms.DataGrid dgMain;
		internal System.Windows.Forms.Button btnLoadData;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public StepByStep6_21()
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
			this.btnLoadData = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.dgMain)).BeginInit();
			this.SuspendLayout();
			// 
			// dgMain
			// 
			this.dgMain.DataMember = "";
			this.dgMain.HeaderForeColor = System.Drawing.SystemColors.ControlText;
			this.dgMain.Location = new System.Drawing.Point(12, 40);
			this.dgMain.Name = "dgMain";
			this.dgMain.Size = new System.Drawing.Size(552, 304);
			this.dgMain.TabIndex = 3;
			// 
			// btnLoadData
			// 
			this.btnLoadData.Location = new System.Drawing.Point(12, 8);
			this.btnLoadData.Name = "btnLoadData";
			this.btnLoadData.TabIndex = 2;
			this.btnLoadData.Text = "Load Data";
			this.btnLoadData.Click += new System.EventHandler(this.btnLoadData_Click);
			// 
			// StepByStep6_21
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(576, 349);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.dgMain,
																		  this.btnLoadData});
			this.Name = "StepByStep6_21";
			this.Text = "StepByStep6_21";
			((System.ComponentModel.ISupportInitialize)(this.dgMain)).EndInit();
			this.ResumeLayout(false);

		}
		#endregion

		[STAThread]
		static void Main() 
		{
			Application.Run(new StepByStep6_21());
		}


		private void btnLoadData_Click(object sender, System.EventArgs e)
		{
			// Create a SqlConnection and a DataSet
			SqlConnection cnn = new SqlConnection("Data Source=(local);" +
			"Initial Catalog=Northwind;Integrated Security=SSPI");
			DataSet ds = new DataSet();

			// Add the customers data to the DataSet
			SqlCommand cmdCustomers= cnn.CreateCommand();
			cmdCustomers.CommandType = CommandType.Text;
			cmdCustomers.CommandText = "SELECT * FROM Customers";
			SqlDataAdapter daCustomers = new SqlDataAdapter();
			daCustomers.SelectCommand = cmdCustomers;
			daCustomers.Fill(ds, "Customers");

			// Add the Orders data to the DataSet
			SqlCommand cmdOrders = cnn.CreateCommand();
			cmdOrders.CommandType = CommandType.Text;
			cmdOrders.CommandText = "SELECT * FROM Orders";
			SqlDataAdapter daOrders = new SqlDataAdapter();
			daOrders.SelectCommand = cmdOrders;
			daOrders.Fill(ds, "Orders");

			// Add the Order Details data to the DataSet
			SqlCommand cmdOrderDetails = cnn.CreateCommand();
			cmdOrderDetails.CommandType = CommandType.Text;
			cmdOrderDetails.CommandText = "SELECT * FROM [Order Details]";
			SqlDataAdapter daOrderDetails = new SqlDataAdapter();
			daOrderDetails.SelectCommand = cmdOrderDetails;
			daOrderDetails.Fill(ds, "OrderDetails");

			// Add Relations
			DataRelation relCustOrder = ds.Relations.Add("CustOrder",
			ds.Tables["Customers"].Columns["CustomerID"],
			ds.Tables["Orders"].Columns["CustomerID"]);

			DataRelation relOrderOrderDetails = ds.Relations.Add("OrderOrderDetails", 
			ds.Tables["Orders"].Columns["OrderID"], 
			ds.Tables["OrderDetails"].Columns["OrderID"]);

			// And show the data on the user interface
			dgMain.DataSource = ds;
			dgMain.DataMember = "Customers";
		
		}
	}
}
