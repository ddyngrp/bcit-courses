using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Data.SqlClient;
using System.IO;

namespace _316C06Exercises
{
	/// <summary>
	/// Summary description for Exercise6_2.
	/// </summary>
	public class Exercise6_2 : System.Windows.Forms.Form
	{
		internal System.Windows.Forms.Button btnWrite;
		internal System.Windows.Forms.ComboBox cboProducts;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public Exercise6_2()
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
			this.btnWrite = new System.Windows.Forms.Button();
			this.cboProducts = new System.Windows.Forms.ComboBox();
			this.SuspendLayout();
			// 
			// btnWrite
			// 
			this.btnWrite.Location = new System.Drawing.Point(16, 48);
			this.btnWrite.Name = "btnWrite";
			this.btnWrite.TabIndex = 3;
			this.btnWrite.Text = "Write File";
			this.btnWrite.Click += new System.EventHandler(this.btnWrite_Click);
			// 
			// cboProducts
			// 
			this.cboProducts.Location = new System.Drawing.Point(16, 8);
			this.cboProducts.Name = "cboProducts";
			this.cboProducts.Size = new System.Drawing.Size(232, 21);
			this.cboProducts.TabIndex = 2;
			this.cboProducts.Text = "ComboBox1";
			// 
			// Exercise6_2
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(292, 273);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.btnWrite,
																		  this.cboProducts});
			this.Name = "Exercise6_2";
			this.Text = "Exercise6_2";
			this.Load += new System.EventHandler(this.Exercise6_2_Load);
			this.ResumeLayout(false);

		}
		#endregion

		[STAThread]
		static void Main() 
		{
			Application.Run(new Exercise6_2());
		}


		SqlConnection cnn = new SqlConnection("Data Source=(local);" +
			"Initial Catalog=Northwind;Integrated Security=SSPI");


		private void btnWrite_Click(object sender, System.EventArgs e)
		{
			// Get a file name to use when saving the file
			SaveFileDialog sfd = new SaveFileDialog();
			sfd.Title = "Choose save file";
			if (sfd.ShowDialog() == DialogResult.OK)
			{
				// Get the full data on the selected product
				SqlCommand cmdProduct = cnn.CreateCommand();
				cmdProduct.CommandType = CommandType.Text;
				cmdProduct.CommandText = "SELECT * FROM Products WHERE ProductID = @ProductID";
				cmdProduct.Parameters.Add(new SqlParameter("@ProductID", SqlDbType.Int));
				cmdProduct.Parameters["@ProductID"].Value = cboProducts.SelectedValue;
				// Open a BinaryWriter
				FileStream fsOut = new FileStream(sfd.FileName, FileMode.Create);
				BinaryWriter bw = new BinaryWriter(fsOut);
				// Get the data into a DataRow
				SqlDataAdapter da = new SqlDataAdapter();
				da.SelectCommand = cmdProduct;
				DataSet ds = new DataSet();
				da.Fill(ds, "Products");
				DataRow dr = ds.Tables["Products"].Rows[0];
				// And write the data
				for (int intI=0; intI <= 9; intI++)
				{
					bw.Write(dr[intI].ToString());
				}
				bw.Flush();
				bw.Close();
				MessageBox.Show("Data written");
			}
		}

		private void Exercise6_2_Load(object sender, System.EventArgs e)
		{
			// Load the customer list
			SqlCommand cmd = cnn.CreateCommand();
			cmd.CommandType = CommandType.Text;
			cmd.CommandText = "SELECT ProductName, ProductID FROM Products ORDER BY ProductName";
			cnn.Open();
			DataSet ds = new DataSet();
			SqlDataAdapter da = new SqlDataAdapter();
			da.SelectCommand = cmd;
			da.Fill(ds, "Products");
			cboProducts.DataSource = ds.Tables["Products"];
			cboProducts.DisplayMember = "ProductName";
			cboProducts.ValueMember = "ProductID";
			cnn.Close();
		}
	}
}
