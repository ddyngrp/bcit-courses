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
	/// Summary description for StepByStep6_26.
	/// </summary>
	public class StepByStep6_26 : System.Windows.Forms.Form
	{
		internal System.Windows.Forms.Button btnDelete;
		private System.Windows.Forms.ComboBox cboCustomerID;
		private System.Windows.Forms.Label label1;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public StepByStep6_26()
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
			this.btnDelete = new System.Windows.Forms.Button();
			this.cboCustomerID = new System.Windows.Forms.ComboBox();
			this.label1 = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// btnDelete
			// 
			this.btnDelete.Location = new System.Drawing.Point(48, 56);
			this.btnDelete.Name = "btnDelete";
			this.btnDelete.Size = new System.Drawing.Size(128, 23);
			this.btnDelete.TabIndex = 1;
			this.btnDelete.Text = "Delete Customer";
			this.btnDelete.Click += new System.EventHandler(this.btnDelete_Click);
			// 
			// cboCustomerID
			// 
			this.cboCustomerID.Location = new System.Drawing.Point(112, 16);
			this.cboCustomerID.Name = "cboCustomerID";
			this.cboCustomerID.Size = new System.Drawing.Size(104, 21);
			this.cboCustomerID.TabIndex = 8;
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(16, 16);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(80, 23);
			this.label1.TabIndex = 7;
			this.label1.Text = "CustomerID";
			// 
			// StepByStep6_26
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(224, 93);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.cboCustomerID,
																		  this.label1,
																		  this.btnDelete});
			this.Name = "StepByStep6_26";
			this.Text = "StepByStep6_26";
			this.Load += new System.EventHandler(this.StepByStep6_26_Load);
			this.ResumeLayout(false);

		}
		#endregion
		[STAThread]
		static void Main() 
		{
			Application.Run(new StepByStep6_26());
		}

		// Create some ADO.NET objects
		SqlConnection cnn = new SqlConnection("Data Source=(local);" +
			"Initial Catalog=Northwind;Integrated Security=SSPI");
		DataSet ds = new DataSet();
		SqlDataAdapter da = new SqlDataAdapter();

		private void StepByStep6_26_Load(object sender, System.EventArgs e)
		{
			// Create a SqlCommand to select data
			SqlCommand cmdSelect = cnn.CreateCommand();
			cmdSelect.CommandType = CommandType.Text;
			cmdSelect.CommandText = "SELECT CustomerID, ContactName FROM Customers";
			// Create a SqlCommand to delete data
			SqlCommand cmdDelete = cnn.CreateCommand();
            cmdDelete.CommandType = CommandType.Text;
			cmdDelete.CommandText = "DELETE FROM Customers WHERE CustomerID = @CustomerID";
			cmdDelete.Parameters.Add("@CustomerID", SqlDbType.NChar,5, "CustomerID");
			cmdDelete.Parameters["@CustomerID"].SourceVersion = DataRowVersion.Original;
			// Set up the DataAdapter and fill the DataSet
			da.SelectCommand = cmdSelect;
			da.DeleteCommand = cmdDelete;
			da.Fill(ds, "Customers");
			// Fill the data in the ComboBox
			cboCustomerID.DisplayMember = "CustomerID";
			cboCustomerID.ValueMember = "CustomerID";
			cboCustomerID.DataSource = ds.Tables["Customers"];
		}

		private void btnDelete_Click(object sender, System.EventArgs e)
		{
			// Find the specified row and delete it
			foreach( DataRow dr in ds.Tables["Customers"].Rows)
			{
				if(dr[0] == cboCustomerID.SelectedValue)
				{
					dr.Delete();
					break;
				}
			}
			// Save the changes
			da.Update(ds, "Customers");
			MessageBox.Show("Row deleted!");
		}
	}
}
