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
	/// Summary description for Exercise6_3.
	/// </summary>
	public class Exercise6_3 : System.Windows.Forms.Form
	{
		internal System.Windows.Forms.Button btnUpdate;
		internal System.Windows.Forms.DataGrid dgMain;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public Exercise6_3()
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
			this.btnUpdate = new System.Windows.Forms.Button();
			this.dgMain = new System.Windows.Forms.DataGrid();
			((System.ComponentModel.ISupportInitialize)(this.dgMain)).BeginInit();
			this.SuspendLayout();
			// 
			// btnUpdate
			// 
			this.btnUpdate.Location = new System.Drawing.Point(8, 320);
			this.btnUpdate.Name = "btnUpdate";
			this.btnUpdate.TabIndex = 3;
			this.btnUpdate.Text = "Update";
			this.btnUpdate.Click += new System.EventHandler(this.btnUpdate_Click);
			// 
			// dgMain
			// 
			this.dgMain.DataMember = "";
			this.dgMain.HeaderForeColor = System.Drawing.SystemColors.ControlText;
			this.dgMain.Location = new System.Drawing.Point(8, 8);
			this.dgMain.Name = "dgMain";
			this.dgMain.Size = new System.Drawing.Size(504, 296);
			this.dgMain.TabIndex = 2;
			// 
			// Exercise6_3
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(584, 349);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.btnUpdate,
																		  this.dgMain});
			this.Name = "Exercise6_3";
			this.Text = "Exercise6_3";
			this.Load += new System.EventHandler(this.Exercise6_3_Load);
			((System.ComponentModel.ISupportInitialize)(this.dgMain)).EndInit();
			this.ResumeLayout(false);

		}
		#endregion

		[STAThread]
		static void Main() 
		{
			Application.Run(new Exercise6_3());
		}


		SqlConnection cnn = new SqlConnection("Data Source=(local);" +
			"Initial Catalog=Northwind;Integrated Security=SSPI");
		DataSet ds = new DataSet();
		SqlDataAdapter daCust = new SqlDataAdapter();
		SqlDataAdapter daOrders = new SqlDataAdapter();

		private void btnUpdate_Click(object sender, System.EventArgs e)
		{
			// Update both datatables
			daCust.Update(ds, "Customers");
			daOrders.Update(ds, "Orders");
		}

		private void Exercise6_3_Load(object sender, System.EventArgs e)
		{
			// Create a SqlCommand to select Customer data
			SqlCommand cmdSelect = cnn.CreateCommand();
			cmdSelect.CommandType = CommandType.Text;
			cmdSelect.CommandText = "SELECT CustomerID, CompanyName, ContactName FROM Customers";
			// Create a SqlCommand to update Customer data
			SqlCommand cmdUpdate = cnn.CreateCommand();
			cmdUpdate.CommandType = CommandType.Text;
			cmdUpdate.CommandText = "UPDATE Customers SET " +
			"CompanyName = @CompanyName, ContactName = @ContactName " +
			"WHERE CustomerID = @CustomerID";
			cmdUpdate.Parameters.Add("@ContactName", SqlDbType.NVarChar,30, "ContactName");
			cmdUpdate.Parameters.Add("@CompanyName", SqlDbType.NVarChar,40, "CompanyName");
			cmdUpdate.Parameters.Add("@CustomerID", SqlDbType.NChar, 5, "CustomerID");
			cmdUpdate.Parameters["@CustomerID"].SourceVersion = DataRowVersion.Original;
			// Create a SqlCommand to insert Customer data
			SqlCommand cmdInsert = cnn.CreateCommand();
			cmdInsert.CommandType = CommandType.Text;
			cmdInsert.CommandText = "INSERT INTO Customers (CustomerID, CompanyName, ContactName) " +
			"VALUES(@CustomerID, @CompanyName, @ContactName)";
			cmdInsert.Parameters.Add("@CustomerID", SqlDbType.NChar, 5, "CustomerID");
			cmdInsert.Parameters.Add("@CompanyName", SqlDbType.NVarChar, 40, "CompanyName");
			cmdInsert.Parameters.Add("@ContactName", SqlDbType.NVarChar, 30, "ContactName");
			cmdInsert.Parameters["@CustomerID"].SourceVersion = DataRowVersion.Original;
			// Create a SqlCommand to delete Customer data
			SqlCommand cmdDelete = cnn.CreateCommand();
			cmdDelete.CommandType = CommandType.Text;
			cmdDelete.CommandText = "DELETE FROM Customers WHERE CustomerID = @CustomerID";
			cmdDelete.Parameters.Add("@CustomerID", SqlDbType.NChar, 5, "CustomerID");
			cmdDelete.Parameters["@CustomerID"].SourceVersion = DataRowVersion.Original;
			// Set up the DataAdapter and fill the DataSet
			daCust.SelectCommand = cmdSelect;
			daCust.UpdateCommand = cmdUpdate;
			daCust.InsertCommand = cmdInsert;
			daCust.DeleteCommand = cmdDelete;
			daCust.Fill(ds, "Customers");
			// Now set up the commands for Orders
			SqlCommand cmdSelectOrders = cnn.CreateCommand();
			cmdSelectOrders.CommandType = CommandType.Text;
			cmdSelectOrders.CommandText = "SELECT OrderID, CustomerID, OrderDate FROM Orders";
			// Create a SqlCommand to update Order data
			SqlCommand cmdUpdateOrders = cnn.CreateCommand();
			cmdUpdateOrders.CommandType = CommandType.Text;
			cmdUpdateOrders.CommandText = "UPDATE Orders SET " +
			"CustomerID = @CustomerID, OrderDate = @OrderDate " +
			"WHERE OrderID = @OrderID";
			cmdUpdateOrders.Parameters.Add("@CustomerID", SqlDbType.NChar, 5, "CustomerID");
			cmdUpdateOrders.Parameters.Add("@OrderDate", SqlDbType.DateTime);
			cmdUpdateOrders.Parameters["@OrderDate"].SourceColumn = "OrderDate";
			cmdUpdateOrders.Parameters.Add("@OrderID", SqlDbType.Int);
			cmdUpdateOrders.Parameters["@OrderID"].SourceColumn = "OrderID";
			cmdUpdateOrders.Parameters["@CustomerID"].SourceVersion = DataRowVersion.Original;
			// Create a SqlCommand to insert Order data
			SqlCommand cmdInsertOrders = cnn.CreateCommand();
			cmdInsertOrders.CommandType = CommandType.Text;
			cmdInsertOrders.CommandText = "INSERT INTO Orders (CustomerID, OrderDate) " +
			"VALUES(@CustomerID, @OrderDate)";
			cmdInsertOrders.Parameters.Add("@CustomerID", SqlDbType.NChar, 5, "CustomerID");
			cmdInsertOrders.Parameters.Add("@OrderDate", SqlDbType.DateTime);
			cmdInsertOrders.Parameters["@OrderDate"].SourceColumn = "OrderDate";
			// Create a SqlCommand to delete Order data
			SqlCommand cmdDeleteOrders = cnn.CreateCommand();
			cmdDeleteOrders.CommandType = CommandType.Text;
			cmdDeleteOrders.CommandText = "DELETE FROM Orders WHERE OrderOD = @OrderID";
			cmdDeleteOrders.Parameters.Add("@OrderID", SqlDbType.Int);
			cmdDeleteOrders.Parameters["@OrderID"].SourceColumn = "OrderID";
			cmdDeleteOrders.Parameters["@OrderID"].SourceVersion = DataRowVersion.Original;
			// Add orders to the DataSet
			daOrders.SelectCommand = cmdSelectOrders;
			daOrders.UpdateCommand = cmdUpdateOrders;
			daOrders.InsertCommand = cmdInsertOrders;
			daOrders.DeleteCommand = cmdDeleteOrders;
			daOrders.Fill(ds, "Orders");
			// Relate the two tables
			DataRelation relCustOrder = ds.Relations.Add("CustOrder", 
			ds.Tables["Customers"].Columns["CustomerID"], 
			ds.Tables["Orders"].Columns["CustomerID"]);
			// And bind the data to the DataGrid
			dgMain.DataSource = ds;
			dgMain.DataMember = "Customers";
		}
	}
}
