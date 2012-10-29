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
	/// Summary description for StepByStep6_24.
	/// </summary>
	public class StepByStep6_24 : System.Windows.Forms.Form
	{
		internal System.Windows.Forms.Button btnUpdate;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox txtContactName;
		private System.Windows.Forms.ComboBox cboCustomerID;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public StepByStep6_24()
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
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.txtContactName = new System.Windows.Forms.TextBox();
			this.cboCustomerID = new System.Windows.Forms.ComboBox();
			this.SuspendLayout();
			// 
			// btnUpdate
			// 
			this.btnUpdate.Location = new System.Drawing.Point(56, 96);
			this.btnUpdate.Name = "btnUpdate";
			this.btnUpdate.Size = new System.Drawing.Size(104, 23);
			this.btnUpdate.TabIndex = 1;
			this.btnUpdate.Text = "Update Contact";
			this.btnUpdate.Click += new System.EventHandler(this.btnUpdate_Click);
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(8, 8);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(80, 23);
			this.label1.TabIndex = 2;
			this.label1.Text = "CustomerID";
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(8, 56);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(80, 23);
			this.label2.TabIndex = 3;
			this.label2.Text = "Contact Name";
			// 
			// txtContactName
			// 
			this.txtContactName.Location = new System.Drawing.Point(104, 48);
			this.txtContactName.Name = "txtContactName";
			this.txtContactName.Size = new System.Drawing.Size(168, 20);
			this.txtContactName.TabIndex = 5;
			this.txtContactName.Text = "";
			// 
			// cboCustomerID
			// 
			this.cboCustomerID.Location = new System.Drawing.Point(104, 8);
			this.cboCustomerID.Name = "cboCustomerID";
			this.cboCustomerID.Size = new System.Drawing.Size(104, 21);
			this.cboCustomerID.TabIndex = 6;
			this.cboCustomerID.SelectedIndexChanged += new System.EventHandler(this.cboCustomerID_SelectedIndexChanged);
			// 
			// StepByStep6_24
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(280, 133);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.cboCustomerID,
																		  this.txtContactName,
																		  this.label2,
																		  this.label1,
																		  this.btnUpdate});
			this.Name = "StepByStep6_24";
			this.Text = "StepByStep6_24";
			this.Load += new System.EventHandler(this.StepByStep6_24_Load);
			this.ResumeLayout(false);

		}
		#endregion

		[STAThread]
		static void Main() 
		{
			Application.Run(new StepByStep6_24());
		}

		// Create some ADO.NET objects
		SqlConnection cnn = new SqlConnection("Data Source=(local);" +
		"Initial Catalog=Northwind;Integrated Security=SSPI");
		DataSet ds = new DataSet();
		SqlDataAdapter da = new SqlDataAdapter();
		DataRow[] adrEdit;

		private void btnUpdate_Click(object sender, System.EventArgs e)
		{
			// Make sure there's some data
			if (adrEdit != null)
			{
				// Prompt for new data and put it in the DataRow
				adrEdit[0]["ContactName"] = txtContactName.Text;
				// And save the changes
				da.Update(ds, "Customers");
				MessageBox.Show("Contact Name Updated!");
			}
		}

		private void StepByStep6_24_Load(object sender, System.EventArgs e)
		{
			// Create a SqlCommand to select data
			SqlCommand cmdSelect = cnn.CreateCommand();
			cmdSelect.CommandType = CommandType.Text;
			cmdSelect.CommandText = "SELECT CustomerID, ContactName FROM Customers";
			// Create a SqlCommand to update data
			SqlCommand cmdUpdate = cnn.CreateCommand();
			cmdUpdate.CommandType = CommandType.Text;
			cmdUpdate.CommandText = "UPDATE Customers SET " +
				"ContactName = @ContactName WHERE CustomerID = @CustomerID";
			cmdUpdate.Parameters.Add("@ContactName", SqlDbType.NVarChar,30, "ContactName");
			cmdUpdate.Parameters.Add("@CustomerID", SqlDbType.NChar,5, "CustomerID");
			cmdUpdate.Parameters["@CustomerID"].SourceVersion = DataRowVersion.Original;
			// Set up the DataAdapter and fill the DataSet
			da.UpdateCommand = cmdUpdate;
			da.SelectCommand = cmdSelect;
			da.Fill(ds, "Customers");
			// Fill the data in the ComboBox
			cboCustomerID.DisplayMember = "CustomerID";
			cboCustomerID.ValueMember = "CustomerID";
			cboCustomerID.DataSource = ds.Tables["Customers"];
		}

		private void cboCustomerID_SelectedIndexChanged(object sender, System.EventArgs e)
		{
			// Get just that customer's DataRow
			adrEdit = ds.Tables["Customers"].Select("CustomerID = '" + cboCustomerID.SelectedValue + "'");
			// Make sure there's some data
			if (adrEdit != null)
			{
				txtContactName.Text = adrEdit[0]["ContactName"].ToString();
			}		
		}
	}
}
