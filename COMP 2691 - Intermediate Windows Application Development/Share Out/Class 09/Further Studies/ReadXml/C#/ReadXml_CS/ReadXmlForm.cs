



using System;
using System.Drawing;
using System.Collections;
using System.IO;
using System.Windows.Forms;
using System.Data;

namespace ReadXml_CS
{
	public class Form1 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.ComboBox SourceData;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Button ButtonLoad;
		private System.Windows.Forms.TextBox Data;
		private System.Windows.Forms.ComboBox ReadMode;
		private System.Windows.Forms.Label ModeUsed;
		private System.Windows.Forms.TextBox FinalSchema;
		private System.Windows.Forms.DataGrid grid;

		public Form1()
		{
			InitializeComponent();
		}


		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.SourceData = new System.Windows.Forms.ComboBox();
			this.label1 = new System.Windows.Forms.Label();
			this.ButtonLoad = new System.Windows.Forms.Button();
			this.Data = new System.Windows.Forms.TextBox();
			this.grid = new System.Windows.Forms.DataGrid();
			this.ReadMode = new System.Windows.Forms.ComboBox();
			this.ModeUsed = new System.Windows.Forms.Label();
			this.FinalSchema = new System.Windows.Forms.TextBox();
			((System.ComponentModel.ISupportInitialize)(this.grid)).BeginInit();
			this.SuspendLayout();
			// 
			// SourceData
			// 
			this.SourceData.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.SourceData.Location = new System.Drawing.Point(8, 32);
			this.SourceData.Name = "SourceData";
			this.SourceData.Size = new System.Drawing.Size(168, 21);
			this.SourceData.TabIndex = 0;
			// 
			// label1
			// 
			this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.label1.Location = new System.Drawing.Point(8, 8);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(136, 23);
			this.label1.TabIndex = 1;
			this.label1.Text = "Pick up a data source";
			this.label1.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
			// 
			// ButtonLoad
			// 
			this.ButtonLoad.Location = new System.Drawing.Point(184, 32);
			this.ButtonLoad.Name = "ButtonLoad";
			this.ButtonLoad.Size = new System.Drawing.Size(72, 21);
			this.ButtonLoad.TabIndex = 2;
			this.ButtonLoad.Text = "Load...";
			this.ButtonLoad.Click += new System.EventHandler(this.ButtonLoad_Click);
			// 
			// Data
			// 
			this.Data.BackColor = System.Drawing.SystemColors.Info;
			this.Data.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.Data.Location = new System.Drawing.Point(8, 64);
			this.Data.Multiline = true;
			this.Data.Name = "Data";
			this.Data.ReadOnly = true;
			this.Data.ScrollBars = System.Windows.Forms.ScrollBars.Both;
			this.Data.Size = new System.Drawing.Size(392, 200);
			this.Data.TabIndex = 3;
			this.Data.Text = "";
			this.Data.WordWrap = false;
			// 
			// grid
			// 
			this.grid.AlternatingBackColor = System.Drawing.Color.GhostWhite;
			this.grid.BackColor = System.Drawing.Color.GhostWhite;
			this.grid.BackgroundColor = System.Drawing.Color.Lavender;
			this.grid.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.grid.CaptionBackColor = System.Drawing.Color.RoyalBlue;
			this.grid.CaptionForeColor = System.Drawing.Color.White;
			this.grid.CaptionText = "Loaded DataSet";
			this.grid.DataMember = "";
			this.grid.FlatMode = true;
			this.grid.Font = new System.Drawing.Font("Tahoma", 8F);
			this.grid.ForeColor = System.Drawing.Color.MidnightBlue;
			this.grid.GridLineColor = System.Drawing.Color.RoyalBlue;
			this.grid.HeaderBackColor = System.Drawing.Color.MidnightBlue;
			this.grid.HeaderFont = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Bold);
			this.grid.HeaderForeColor = System.Drawing.Color.Lavender;
			this.grid.LinkColor = System.Drawing.Color.Teal;
			this.grid.Location = new System.Drawing.Point(408, 8);
			this.grid.Name = "grid";
			this.grid.ParentRowsBackColor = System.Drawing.Color.Lavender;
			this.grid.ParentRowsForeColor = System.Drawing.Color.MidnightBlue;
			this.grid.SelectionBackColor = System.Drawing.Color.Teal;
			this.grid.SelectionForeColor = System.Drawing.Color.PaleGreen;
			this.grid.Size = new System.Drawing.Size(312, 256);
			this.grid.TabIndex = 4;
			// 
			// ReadMode
			// 
			this.ReadMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.ReadMode.Location = new System.Drawing.Point(264, 32);
			this.ReadMode.Name = "ReadMode";
			this.ReadMode.Size = new System.Drawing.Size(136, 21);
			this.ReadMode.TabIndex = 5;
			this.ReadMode.SelectedIndexChanged += new System.EventHandler(this.ReadMode_SelectedIndexChanged);
			// 
			// ModeUsed
			// 
			this.ModeUsed.Location = new System.Drawing.Point(264, 16);
			this.ModeUsed.Name = "ModeUsed";
			this.ModeUsed.Size = new System.Drawing.Size(136, 16);
			this.ModeUsed.TabIndex = 6;
			// 
			// FinalSchema
			// 
			this.FinalSchema.BackColor = System.Drawing.Color.Lavender;
			this.FinalSchema.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.FinalSchema.Location = new System.Drawing.Point(8, 272);
			this.FinalSchema.Multiline = true;
			this.FinalSchema.Name = "FinalSchema";
			this.FinalSchema.ReadOnly = true;
			this.FinalSchema.ScrollBars = System.Windows.Forms.ScrollBars.Both;
			this.FinalSchema.Size = new System.Drawing.Size(712, 248);
			this.FinalSchema.TabIndex = 7;
			this.FinalSchema.Text = "";
			this.FinalSchema.WordWrap = false;
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(728, 535);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.FinalSchema,
																		  this.ModeUsed,
																		  this.ReadMode,
																		  this.grid,
																		  this.Data,
																		  this.ButtonLoad,
																		  this.label1,
																		  this.SourceData});
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.Name = "Form1";
			this.Text = "Demonstrating ReadXml...";
			this.Load += new System.EventHandler(this.Form1_Load);
			((System.ComponentModel.ISupportInitialize)(this.grid)).EndInit();
			this.ResumeLayout(false);

		}
		#endregion

		[STAThread]
		static void Main() 
		{
			Application.Run(new Form1());
		}



		// ***************************************************************************
		// Initialize the form
		private void Form1_Load(object sender, System.EventArgs e)
		{
			// Populate the list with the available sources
			SourceData.Items.Add("Employees.xml");
			SourceData.Items.Add("EmpAttrib.xml");
			SourceData.Items.Add("Folders.xml");
			SourceData.Items.Add("Class.xml");
			SourceData.Items.Add("RefClass.xml");
			SourceData.SelectedIndex = 0;

			// Populate the list with the available list modes
			ReadMode.DataSource = Enum.GetValues(typeof(XmlReadMode)); 
		}
		// ***************************************************************************

		// ***************************************************************************
		// Load the currently selected XML source
		private void ButtonLoad_Click(object sender, System.EventArgs e)
		{
			string fileName = SourceData.SelectedItem.ToString(); 
			LoadAndDisplay(fileName);
		}
		// ***************************************************************************

		// ***************************************************************************
		// Read and display the specified XML file and loads it into a DataSet
		void LoadAndDisplay(string fileName)
		{
			// Display the XML source in a textbox
			StreamReader fr = new StreamReader(fileName);
			Data.Text = fr.ReadToEnd();
			fr.Close();

			// Load a DataSet
			XmlReadMode mode = (XmlReadMode) Enum.Parse(typeof(XmlReadMode), ReadMode.SelectedItem.ToString());
			DataSet ds = new DataSet();
			XmlReadMode used = ds.ReadXml(fileName, mode);

			// Show the DataSet
			grid.DataSource = ds;
			ModeUsed.Text = "Used \"" + used.ToString() + "\"";

			// Show the recognized (and used) schema
			StringWriter writer = new StringWriter();
			ds.WriteXmlSchema(writer);
			FinalSchema.Text = writer.ToString();
			writer.Close();
		}
		// ***************************************************************************

		// ***************************************************************************
		// The currently selected read mode
		private void ReadMode_SelectedIndexChanged(object sender, System.EventArgs e)
		{
			ModeUsed.Text = "Will use \"" + ReadMode.SelectedItem.ToString() + "\"";
		}
		// ***************************************************************************

	}
}
