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
	/// Summary description for StepByStep6_25.
	/// </summary>
	public class StepByStep6_25 : System.Windows.Forms.Form
	{
		internal System.Windows.Forms.Button btnAdd;
		internal System.Windows.Forms.TextBox txtContactName;
		internal System.Windows.Forms.Label Label4;
		internal System.Windows.Forms.TextBox txtCompanyName;
		internal System.Windows.Forms.Label Label3;
		internal System.Windows.Forms.TextBox txtCustomerID;
		internal System.Windows.Forms.Label Label2;
		internal System.Windows.Forms.Label Label1;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public StepByStep6_25()
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
			this.btnAdd = new System.Windows.Forms.Button();
			this.txtContactName = new System.Windows.Forms.TextBox();
			this.Label4 = new System.Windows.Forms.Label();
			this.txtCompanyName = new System.Windows.Forms.TextBox();
			this.Label3 = new System.Windows.Forms.Label();
			this.txtCustomerID = new System.Windows.Forms.TextBox();
			this.Label2 = new System.Windows.Forms.Label();
			this.Label1 = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// btnAdd
			// 
			this.btnAdd.Location = new System.Drawing.Point(192, 144);
			this.btnAdd.Name = "btnAdd";
			this.btnAdd.TabIndex = 15;
			this.btnAdd.Text = "Add";
			this.btnAdd.Click += new System.EventHandler(this.btnAdd_Click);
			// 
			// txtContactName
			// 
			this.txtContactName.Location = new System.Drawing.Point(112, 104);
			this.txtContactName.Name = "txtContactName";
			this.txtContactName.Size = new System.Drawing.Size(160, 20);
			this.txtContactName.TabIndex = 14;
			this.txtContactName.Text = "";
			// 
			// Label4
			// 
			this.Label4.Location = new System.Drawing.Point(0, 104);
			this.Label4.Name = "Label4";
			this.Label4.Size = new System.Drawing.Size(100, 24);
			this.Label4.TabIndex = 13;
			this.Label4.Text = "Contact Name";
			// 
			// txtCompanyName
			// 
			this.txtCompanyName.Location = new System.Drawing.Point(112, 72);
			this.txtCompanyName.Name = "txtCompanyName";
			this.txtCompanyName.Size = new System.Drawing.Size(160, 20);
			this.txtCompanyName.TabIndex = 12;
			this.txtCompanyName.Text = "";
			// 
			// Label3
			// 
			this.Label3.Location = new System.Drawing.Point(0, 72);
			this.Label3.Name = "Label3";
			this.Label3.Size = new System.Drawing.Size(100, 24);
			this.Label3.TabIndex = 11;
			this.Label3.Text = "Company Name";
			// 
			// txtCustomerID
			// 
			this.txtCustomerID.Location = new System.Drawing.Point(112, 40);
			this.txtCustomerID.Name = "txtCustomerID";
			this.txtCustomerID.TabIndex = 10;
			this.txtCustomerID.Text = "";
			// 
			// Label2
			// 
			this.Label2.Location = new System.Drawing.Point(0, 40);
			this.Label2.Name = "Label2";
			this.Label2.Size = new System.Drawing.Size(100, 24);
			this.Label2.TabIndex = 9;
			this.Label2.Text = "CustomerID";
			// 
			// Label1
			// 
			this.Label1.Location = new System.Drawing.Point(0, 8);
			this.Label1.Name = "Label1";
			this.Label1.Size = new System.Drawing.Size(272, 16);
			this.Label1.TabIndex = 8;
			this.Label1.Text = "Fill in requested information and click Add";
			// 
			// StepByStep6_25
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(292, 181);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.btnAdd,
																		  this.txtContactName,
																		  this.Label4,
																		  this.txtCompanyName,
																		  this.Label3,
																		  this.txtCustomerID,
																		  this.Label2,
																		  this.Label1});
			this.Name = "StepByStep6_25";
			this.Text = "StepByStep6_25";
			this.Load += new System.EventHandler(this.StepByStep6_25_Load);
			this.ResumeLayout(false);

		}
		#endregion

		[STAThread]
		static void Main() 
		{
			Application.Run(new StepByStep6_25());
		}

		// Create some ADO.NET objects
		SqlConnection cnn = new SqlConnection("Data Source=(local);" +
			"Initial Catalog=Northwind;Integrated Security=SSPI");
		DataSet ds = new DataSet();
		SqlDataAdapter da = new SqlDataAdapter();

		private void StepByStep6_25_Load(object sender, System.EventArgs e)
		{
			// Create a SqlCommand to select data
			SqlCommand cmdSelect = cnn.CreateCommand();
			cmdSelect.CommandType = CommandType.Text;
			cmdSelect.CommandText = "SELECT CustomerID, CompanyName, " +
			"ContactName FROM Customers";
			// Create a SqlCommand to insert data
			SqlCommand cmdInsert = cnn.CreateCommand();
			cmdInsert.CommandType = CommandType.Text;
			cmdInsert.CommandText = "INSERT INTO Customers " +
			"(CustomerID, CompanyName, ContactName) " +
			"VALUES(@CustomerID, @CompanyName, @ContactName)";
			cmdInsert.Parameters.Add("@CustomerID", SqlDbType.NChar,5, "CustomerID");
			cmdInsert.Parameters.Add("@CompanyName", SqlDbType.NVarChar,40, "CompanyName");
			cmdInsert.Parameters.Add("@ContactName", SqlDbType.NVarChar,30, "ContactName");
			cmdInsert.Parameters["@CustomerID"].SourceVersion = DataRowVersion.Original;
			// Set up the DataAdapter and fill the DataSet
			da.SelectCommand = cmdSelect;
			da.InsertCommand = cmdInsert;
			da.Fill(ds, "Customers");
		}

		private void btnAdd_Click(object sender, System.EventArgs e)
		{
			// Create a new DataRow
			DataRow dr = ds.Tables["Customers"].NewRow();
			// Set values
			dr[0] = txtCustomerID.Text;
			dr[1] = txtCompanyName.Text;
			dr[2] = txtContactName.Text;
			// And append the new row to the DataTable
			ds.Tables["Customers"].Rows.Add(dr);
			// Now save back to the database
			da.Update(ds, "Customers");
			MessageBox.Show("Row added!");
		}

	}
}
