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
	/// Summary description for StepByStep6_18.
	/// </summary>
	public class StepByStep6_18 : System.Windows.Forms.Form
	{
		internal System.Windows.Forms.DataGrid dgProducts;
		internal System.Windows.Forms.Button btnLoad;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public StepByStep6_18()
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
			this.dgProducts = new System.Windows.Forms.DataGrid();
			this.btnLoad = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.dgProducts)).BeginInit();
			this.SuspendLayout();
			// 
			// dgProducts
			// 
			this.dgProducts.CaptionText = "Products";
			this.dgProducts.DataMember = "";
			this.dgProducts.HeaderForeColor = System.Drawing.SystemColors.ControlText;
			this.dgProducts.Location = new System.Drawing.Point(12, 38);
			this.dgProducts.Name = "dgProducts";
			this.dgProducts.Size = new System.Drawing.Size(520, 282);
			this.dgProducts.TabIndex = 3;
			// 
			// btnLoad
			// 
			this.btnLoad.Location = new System.Drawing.Point(12, 6);
			this.btnLoad.Name = "btnLoad";
			this.btnLoad.TabIndex = 2;
			this.btnLoad.Text = "Load Data";
			this.btnLoad.Click += new System.EventHandler(this.btnLoad_Click);
			// 
			// StepByStep6_18
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(544, 325);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.dgProducts,
																		  this.btnLoad});
			this.Name = "StepByStep6_18";
			this.Text = "StepByStep6_18";
			((System.ComponentModel.ISupportInitialize)(this.dgProducts)).EndInit();
			this.ResumeLayout(false);

		}
		#endregion

		[STAThread]
		static void Main() 
		{
			Application.Run(new StepByStep6_18());
		}


		private void btnLoad_Click(object sender, System.EventArgs e)
		{
			// Create a SqlConnection
			SqlConnection cnn = new SqlConnection("Data Source=(local);" +
			"Initial Catalog=Northwind;Integrated Security=SSPI");
			// Create a SqlCommand
			SqlCommand cmd = cnn.CreateCommand();
			cmd.CommandType = CommandType.Text;
			cmd.CommandText = "SELECT * FROM Products ORDER BY ProductName";
			// Set up the DataAdapter and fill the DataSet
			SqlDataAdapter da = new SqlDataAdapter();
			da.SelectCommand = cmd;
			DataSet ds = new DataSet();
			// Display the data on the user interface
			da.Fill(ds, "Products");
			dgProducts.DataSource = ds;
			dgProducts.DataMember = "Products";
		}
	}
}
