


using System;
using System.Drawing;
using System.Collections;
using System.Windows.Forms;
using System.Data;
using System.Data.SqlClient;
using System.Xml;
using System.IO;


namespace WriteXml_CS
{
	public class Form1 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox TerritoriesCommand;
		private System.Windows.Forms.TextBox EmployeesCommand;
		private System.Windows.Forms.Button ButtonSave;
		private System.Windows.Forms.CheckedListBox ColumnSettings;
		private System.Windows.Forms.CheckBox Check_Nested;
		private System.Windows.Forms.CheckBox Check_WithSchema;
		private System.Windows.Forms.TextBox OutputText;
		private System.Windows.Forms.TextBox TableName2;
		private System.Windows.Forms.TextBox TableName1;
		private System.Windows.Forms.TextBox DataSetName;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.StatusBar appStatusBar;
		private System.Windows.Forms.CheckBox Check_Relation;
		private System.Windows.Forms.CheckBox Check_Validating;
		private System.Windows.Forms.Label label3;

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
			this.EmployeesCommand = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.TerritoriesCommand = new System.Windows.Forms.TextBox();
			this.ButtonSave = new System.Windows.Forms.Button();
			this.Check_WithSchema = new System.Windows.Forms.CheckBox();
			this.Check_Nested = new System.Windows.Forms.CheckBox();
			this.ColumnSettings = new System.Windows.Forms.CheckedListBox();
			this.OutputText = new System.Windows.Forms.TextBox();
			this.label3 = new System.Windows.Forms.Label();
			this.TableName1 = new System.Windows.Forms.TextBox();
			this.TableName2 = new System.Windows.Forms.TextBox();
			this.DataSetName = new System.Windows.Forms.TextBox();
			this.label4 = new System.Windows.Forms.Label();
			this.appStatusBar = new System.Windows.Forms.StatusBar();
			this.Check_Relation = new System.Windows.Forms.CheckBox();
			this.Check_Validating = new System.Windows.Forms.CheckBox();
			this.SuspendLayout();
			// 
			// EmployeesCommand
			// 
			this.EmployeesCommand.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.EmployeesCommand.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.EmployeesCommand.Location = new System.Drawing.Point(80, 16);
			this.EmployeesCommand.Name = "EmployeesCommand";
			this.EmployeesCommand.Size = new System.Drawing.Size(456, 20);
			this.EmployeesCommand.TabIndex = 0;
			this.EmployeesCommand.Text = "SELECT employeeid, lastname, firstname FROM employees";
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(0, 16);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(72, 20);
			this.label1.TabIndex = 1;
			this.label1.Text = "Command";
			this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(0, 40);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(72, 20);
			this.label2.TabIndex = 3;
			this.label2.Text = "Command";
			this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// TerritoriesCommand
			// 
			this.TerritoriesCommand.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.TerritoriesCommand.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.TerritoriesCommand.Location = new System.Drawing.Point(80, 40);
			this.TerritoriesCommand.Name = "TerritoriesCommand";
			this.TerritoriesCommand.Size = new System.Drawing.Size(456, 20);
			this.TerritoriesCommand.TabIndex = 2;
			this.TerritoriesCommand.Text = "SELECT TOP 10 employeeid, territoryid FROM employeeterritories";
			// 
			// ButtonSave
			// 
			this.ButtonSave.Location = new System.Drawing.Point(680, 16);
			this.ButtonSave.Name = "ButtonSave";
			this.ButtonSave.Size = new System.Drawing.Size(80, 40);
			this.ButtonSave.TabIndex = 4;
			this.ButtonSave.Text = "Save...";
			this.ButtonSave.Click += new System.EventHandler(this.ButtonSave_Click);
			// 
			// Check_WithSchema
			// 
			this.Check_WithSchema.Location = new System.Drawing.Point(8, 176);
			this.Check_WithSchema.Name = "Check_WithSchema";
			this.Check_WithSchema.Size = new System.Drawing.Size(152, 24);
			this.Check_WithSchema.TabIndex = 5;
			this.Check_WithSchema.Text = "Save with schema";
			// 
			// Check_Nested
			// 
			this.Check_Nested.Location = new System.Drawing.Point(40, 224);
			this.Check_Nested.Name = "Check_Nested";
			this.Check_Nested.Size = new System.Drawing.Size(112, 24);
			this.Check_Nested.TabIndex = 6;
			this.Check_Nested.Text = "Nested Relations";
			// 
			// ColumnSettings
			// 
			this.ColumnSettings.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.ColumnSettings.Location = new System.Drawing.Point(8, 96);
			this.ColumnSettings.Name = "ColumnSettings";
			this.ColumnSettings.Size = new System.Drawing.Size(168, 77);
			this.ColumnSettings.TabIndex = 8;
			// 
			// OutputText
			// 
			this.OutputText.Anchor = (((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
				| System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right);
			this.OutputText.BackColor = System.Drawing.SystemColors.Info;
			this.OutputText.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.OutputText.Location = new System.Drawing.Point(192, 80);
			this.OutputText.Multiline = true;
			this.OutputText.Name = "OutputText";
			this.OutputText.ReadOnly = true;
			this.OutputText.ScrollBars = System.Windows.Forms.ScrollBars.Both;
			this.OutputText.Size = new System.Drawing.Size(568, 248);
			this.OutputText.TabIndex = 9;
			this.OutputText.Text = "";
			this.OutputText.WordWrap = false;
			// 
			// label3
			// 
			this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.label3.Location = new System.Drawing.Point(8, 72);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(168, 20);
			this.label3.TabIndex = 10;
			this.label3.Text = "Check to render as an attribute";
			this.label3.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
			// 
			// TableName1
			// 
			this.TableName1.BackColor = System.Drawing.Color.PapayaWhip;
			this.TableName1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.TableName1.Location = new System.Drawing.Point(544, 16);
			this.TableName1.Name = "TableName1";
			this.TableName1.Size = new System.Drawing.Size(120, 20);
			this.TableName1.TabIndex = 11;
			this.TableName1.Text = "Employees";
			// 
			// TableName2
			// 
			this.TableName2.BackColor = System.Drawing.Color.PapayaWhip;
			this.TableName2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.TableName2.Location = new System.Drawing.Point(544, 40);
			this.TableName2.Name = "TableName2";
			this.TableName2.Size = new System.Drawing.Size(120, 20);
			this.TableName2.TabIndex = 12;
			this.TableName2.Text = "Territories";
			// 
			// DataSetName
			// 
			this.DataSetName.BackColor = System.Drawing.Color.PapayaWhip;
			this.DataSetName.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.DataSetName.Location = new System.Drawing.Point(8, 304);
			this.DataSetName.Name = "DataSetName";
			this.DataSetName.Size = new System.Drawing.Size(168, 20);
			this.DataSetName.TabIndex = 13;
			this.DataSetName.Text = "NorthwindInfo";
			// 
			// label4
			// 
			this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.label4.Location = new System.Drawing.Point(8, 280);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(168, 20);
			this.label4.TabIndex = 14;
			this.label4.Text = "Name of the DataSet";
			this.label4.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
			// 
			// appStatusBar
			// 
			this.appStatusBar.Location = new System.Drawing.Point(0, 337);
			this.appStatusBar.Name = "appStatusBar";
			this.appStatusBar.Size = new System.Drawing.Size(768, 22);
			this.appStatusBar.TabIndex = 15;
			this.appStatusBar.Text = "Ready";
			// 
			// Check_Relation
			// 
			this.Check_Relation.Location = new System.Drawing.Point(8, 200);
			this.Check_Relation.Name = "Check_Relation";
			this.Check_Relation.Size = new System.Drawing.Size(112, 24);
			this.Check_Relation.TabIndex = 16;
			this.Check_Relation.Text = "Create a relation";
			// 
			// Check_Validating
			// 
			this.Check_Validating.Location = new System.Drawing.Point(8, 256);
			this.Check_Validating.Name = "Check_Validating";
			this.Check_Validating.Size = new System.Drawing.Size(152, 24);
			this.Check_Validating.TabIndex = 17;
			this.Check_Validating.Text = "Create validating output ";
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(768, 359);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.Check_Validating,
																		  this.Check_Relation,
																		  this.appStatusBar,
																		  this.label4,
																		  this.DataSetName,
																		  this.TableName2,
																		  this.TableName1,
																		  this.label3,
																		  this.OutputText,
																		  this.ColumnSettings,
																		  this.Check_Nested,
																		  this.Check_WithSchema,
																		  this.ButtonSave,
																		  this.label2,
																		  this.TerritoriesCommand,
																		  this.label1,
																		  this.EmployeesCommand});
			this.Name = "Form1";
			this.Text = "Writing DataSets to XML...";
			this.Load += new System.EventHandler(this.Form1_Load);
			this.ResumeLayout(false);

		}
		#endregion

		[STAThread]

		static void Main() 
		{
			Application.Run(new Form1());
		}

		
		
		// **********************************************************
		// Execute the queries and save the resultant DataSet to XML
		private void ButtonSave_Click(object sender, System.EventArgs e)
		{
			appStatusBar.Text = "Working...";
			DataSet ds = LoadData();
			SaveData(ds);
			appStatusBar.Text = "Ready";
		}
		// **********************************************************

		// **********************************************************
		// Load the data into a DataSet
		private DataSet LoadData() 
		{
			string nwind = "DATABASE=northwind;SERVER=localhost;UID=sa;";
			SqlConnection conn = new SqlConnection(nwind);
			SqlDataAdapter adapter = new SqlDataAdapter();

			// Prepare commands
			SqlCommand cmd1 = new SqlCommand(EmployeesCommand.Text, conn);
			SqlCommand cmd2 = new SqlCommand(TerritoriesCommand.Text, conn);
			DataSet ds = new DataSet(DataSetName.Text);

			// Execute
			conn.Open();
			adapter.SelectCommand = cmd1;
			adapter.Fill(ds, TableName1.Text);
			adapter.SelectCommand = cmd2;
			adapter.Fill(ds, TableName2.Text);
			conn.Close();

			// Set the relation
			if (Check_Relation.Checked)
			{
				DataRelation rel = new DataRelation("Emp2Terr", 
					ds.Tables[TableName1.Text].Columns["employeeid"],
					ds.Tables[TableName2.Text].Columns["employeeid"]);
				rel.Nested = Check_Nested.Checked;
				ds.Relations.Add(rel);
			}

			// Add extended properties to the tables
			ds.Tables[TableName1.Text].ExtendedProperties.Add("Command", EmployeesCommand.Text);
			ds.Tables[TableName2.Text].ExtendedProperties.Add("Command", TerritoriesCommand.Text);

			// Set the column mappings
			for(int i=0; i<ColumnSettings.Items.Count; i++)
			{
				if (ColumnSettings.GetItemChecked(i))
				{
					string colName = ColumnSettings.Items[i].ToString();
					ArrayList a = (ArrayList) ColumnSettings.Tag;
					ds.Tables[Convert.ToInt32(a[i])].Columns[colName].ColumnMapping = MappingType.Attribute;
				}
			}

			return ds;
		}
		// **********************************************************

		// **********************************************************
		// Save the DataSet according to the specified settings
		private void SaveData(DataSet ds)
		{
			// Save to disk
          
			StringWriter sw = new StringWriter();
			XmlTextWriter writer = new XmlTextWriter(sw);
            
			writer.Formatting = Formatting.Indented; 

			if (Check_Validating.Checked)
			{
				writer.WriteStartElement("de", "Wrapper", "dinoe-xml-07356-1801-1");	
				ds.WriteXmlSchema(writer);
				ds.WriteXml(writer);
				writer.WriteEndElement();
                               
			}
			else
				ds.WriteXml(writer, 
					(Check_WithSchema.Checked ?XmlWriteMode.WriteSchema :XmlWriteMode.IgnoreSchema));

			// Show the saved data
            
			writer.Close();
			OutputText.Text = sw.ToString();
          
           
            
		}
		// **********************************************************

		// **********************************************************
		// Filling the checked listbox
		private void Form1_Load(object sender, System.EventArgs e)
		{
			ArrayList a = new ArrayList();
			ColumnSettings.Tag = a;
			ColumnSettings.Items.Add("employeeid");
			a.Add(0);
			ColumnSettings.Items.Add("lastname");
			a.Add(0);
			ColumnSettings.Items.Add("firstname");
			a.Add(0);
			ColumnSettings.Items.Add("employeeid");
			a.Add(1);
			ColumnSettings.Items.Add("territoryid");
			a.Add(1);
		}
		// **********************************************************

	}
}
