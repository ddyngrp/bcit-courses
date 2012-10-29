using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using System.Collections;
using System.Data.SqlClient;
using System.Xml;
using System.IO;




namespace XMLdotNET.WriteXML
{
    public partial class WriteXML : Form
    {
        public WriteXML()
        {
            InitializeComponent();
        }
        
        // **********************************************************
        // Execute the queries and save the resultant DataSet to XML
        private void ButtonSave_Click(object sender, EventArgs e)
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
            string nwind = "DATABASE=northwind;SERVER=www.j2ee.ca;UID=aspx;password=aspx;";
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
            for (int i = 0; i < ColumnSettings.Items.Count; i++)
            {
                if (ColumnSettings.GetItemChecked(i))
                {
                    string colName = ColumnSettings.Items[i].ToString();
                    ArrayList a = (ArrayList)ColumnSettings.Tag;
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
                    (Check_WithSchema.Checked ? XmlWriteMode.WriteSchema : XmlWriteMode.IgnoreSchema));

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
        // Filling the checked listbox
        private void WriteXML_Load(object sender, EventArgs e)
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