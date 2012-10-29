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
	/// Summary description for StepByStep6_27.
	/// </summary>
	public class StepByStep6_27 : System.Windows.Forms.Form
	{
		internal System.Windows.Forms.DataGrid dgCustomers;
		internal System.Windows.Forms.Button btnSaveChanges;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public StepByStep6_27()
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
			this.btnSaveChanges = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.dgCustomers)).BeginInit();
			this.SuspendLayout();
			// 
			// dgCustomers
			// 
			this.dgCustomers.DataMember = "";
			this.dgCustomers.HeaderForeColor = System.Drawing.SystemColors.ControlText;
			this.dgCustomers.Location = new System.Drawing.Point(8, 0);
			this.dgCustomers.Name = "dgCustomers";
			this.dgCustomers.Size = new System.Drawing.Size(496, 360);
			this.dgCustomers.TabIndex = 1;
			// 
			// btnSaveChanges
			// 
			this.btnSaveChanges.Location = new System.Drawing.Point(8, 368);
			this.btnSaveChanges.Name = "btnSaveChanges";
			this.btnSaveChanges.Size = new System.Drawing.Size(88, 23);
			this.btnSaveChanges.TabIndex = 2;
			this.btnSaveChanges.Text = "Save Changes";
			this.btnSaveChanges.Click += new System.EventHandler(this.btnSaveChanges_Click);
			// 
			// StepByStep6_27
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(512, 397);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.btnSaveChanges,
																		  this.dgCustomers});
			this.Name = "StepByStep6_27";
			this.Text = "StepByStep6_27";
			this.Load += new System.EventHandler(this.StepByStep6_27_Load);
			((System.ComponentModel.ISupportInitialize)(this.dgCustomers)).EndInit();
			this.ResumeLayout(false);

		}
		#endregion

		[STAThread]
		static void Main() 
		{
			Application.Run(new StepByStep6_27());
		}

		// Create some ADO.NET objects
		SqlConnection cnn = new SqlConnection("Data Source=(local);" +
			"Initial Catalog=Northwind;Integrated Security=SSPI");
		DataSet ds = new DataSet();
		SqlDataAdapter da = new SqlDataAdapter();


		private void StepByStep6_27_Load(object sender, System.EventArgs e)
		{
			// Create a SqlCommand to select data
			SqlCommand cmdSelect = cnn.CreateCommand();
			cmdSelect.CommandType = CommandType.Text;
			cmdSelect.CommandText = "SELECT CustomerID, CompanyName, ContactName FROM Customers";
			// Create a SqlCommand to update data
			SqlCommand cmdUpdate = cnn.CreateCommand();
			cmdUpdate.CommandType = CommandType.Text;
			cmdUpdate.CommandText = "UPDATE Customers SET " +
			"CompanyName = @CompanyName, ContactName = @ContactName " +
			"WHERE CustomerID = @CustomerID";
			cmdUpdate.Parameters.Add("@ContactName", SqlDbType.NVarChar, 30, "ContactName");
			cmdUpdate.Parameters.Add("@CompanyName", SqlDbType.NVarChar, 40, "CompanyName");
			cmdUpdate.Parameters.Add("@CustomerID", SqlDbType.NChar, 5, "CustomerID");
			cmdUpdate.Parameters["@CustomerID"].SourceVersion = DataRowVersion.Original;
			// Create a SqlCommand to insert data
			SqlCommand cmdInsert= cnn.CreateCommand();
			cmdInsert.CommandType = CommandType.Text;
			cmdInsert.CommandText = "INSERT INTO Customers " +
			"(CustomerID, CompanyName, ContactName) " +
			"VALUES(@CustomerID, @CompanyName, @ContactName)";
			cmdInsert.Parameters.Add("@CustomerID", SqlDbType.NChar,5, "CustomerID");
			cmdInsert.Parameters.Add("@CompanyName", SqlDbType.NVarChar, 40, "CompanyName");
			cmdInsert.Parameters.Add("@ContactName", SqlDbType.NVarChar, 30, "ContactName");
			cmdInsert.Parameters["@CustomerID"].SourceVersion = DataRowVersion.Original;
			// Create a SqlCommand to delete data
			SqlCommand cmdDelete = cnn.CreateCommand();
			cmdDelete.CommandType = CommandType.Text;
			cmdDelete.CommandText = "DELETE FROM Customers WHERE CustomerID = @CustomerID";
			cmdDelete.Parameters.Add("@CustomerID", SqlDbType.NChar, 5, "CustomerID");
			cmdDelete.Parameters["@CustomerID"].SourceVersion = DataRowVersion.Original;
			// Set up the DataAdapter and fill the DataSet
			da.SelectCommand = cmdSelect;
			da.UpdateCommand = cmdUpdate;
			da.InsertCommand = cmdInsert;
			da.DeleteCommand = cmdDelete;
			da.Fill(ds, "Customers");
			// And bind the data to the DataGrid
			dgCustomers.DataSource = ds;
			dgCustomers.DataMember = "Customers";
		}

		private void btnSaveChanges_Click(object sender, System.EventArgs e)
		{
	        // Persist all changes from the data model to the database
			da.Update(ds, "Customers");
		}
	}
}
