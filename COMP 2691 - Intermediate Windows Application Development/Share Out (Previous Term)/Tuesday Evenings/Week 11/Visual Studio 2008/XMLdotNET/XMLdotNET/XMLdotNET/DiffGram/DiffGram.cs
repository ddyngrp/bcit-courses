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
using System.Xml.Serialization;



//    Persisting DataSet objects to XML diffgrams...


namespace XMLdotNET.DiffGram
{
    public partial class DiffGram : Form
    {
        public DiffGram()
        {
            InitializeComponent();
        }


        // **********************************************************
        // Properties
        protected string Url = Environment.CurrentDirectory + "\\_diffgr_.xml";
        protected DataSet m_data = null;
        // **********************************************************

        // **********************************************************
        // Execute the queries and save the resultant DataSet to XML
        private void ButtonSave_Click(object sender, EventArgs e)
        {
            appStatusBar.Text = "Working...";
            m_data = LoadData();
            SaveData(m_data, true, Check_WithSchema.Checked);
            ButtonEdit.Enabled = true;
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
            adapter.MissingSchemaAction = MissingSchemaAction.AddWithKey;

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

            // Set the (nested) relation
            if (Check_Nested.Checked)
            {
                DataRelation rel = new DataRelation("Emp2Terr",
                    ds.Tables[TableName1.Text].Columns["employeeid"],
                    ds.Tables[TableName2.Text].Columns["employeeid"]);
                rel.Nested = true;
                ds.Relations.Add(rel);
            }

            // Set the column mappings
            try
            {
                for (int i = 0; i < ColumnSettings.Items.Count; i++)
                {
                    if (ColumnSettings.GetItemChecked(i))
                    {
                        string colName = ColumnSettings.Items[i].ToString();
                        ArrayList a = (ArrayList)ColumnSettings.Tag;
                        ds.Tables[Convert.ToInt32(a[i])].Columns[colName].ColumnMapping = MappingType.Attribute;
                    }
                }
            }
            catch { }

            // Hide the Employees.employeeid column (overriding previous setting)
            if (Check_Hidden.Checked)
                ds.Tables[TableName1.Text].Columns["employeeid"].ColumnMapping = MappingType.Hidden;

            return ds;
        }
        // **********************************************************

        // **********************************************************
        // Save the DataSet according to the specified settings
        private void SaveData(DataSet ds, bool saveAsFile, bool bUseSchema)
        {
            if (saveAsFile)
                DiffGramToFile(ds, Url, bUseSchema);
            else
                DiffGramToString(ds, bUseSchema);
        }
        // **********************************************************

        // **********************************************************
        // Saves the DataSet as a Diffgram to an in-memory string
        private void DiffGramToString(DataSet ds, bool bUseSchema)
        {
            // Save to disk
            StringWriter sw = new StringWriter();
            XmlTextWriter writer = new XmlTextWriter(sw);
            writer.Formatting = Formatting.Indented;

            // Create the diffgram
            if (!bUseSchema)
                ds.WriteXml(writer, XmlWriteMode.DiffGram);
            else
            {
                XmlSerializer ser = new XmlSerializer(typeof(DataSet));
                ser.Serialize(writer, ds);
            }

            // Show the saved data
            writer.Close();
            OutputText.Text = sw.ToString();
        }
        // **********************************************************

        // **********************************************************
        // Saves the DataSet as a Diffgram to a disk file
        private void DiffGramToFile(DataSet ds, string fileName, bool bUseSchema)
        {
            // Save to disk
            StreamWriter sw = new StreamWriter(fileName);
            XmlTextWriter writer = new XmlTextWriter(sw);
            writer.Formatting = Formatting.Indented;

            // Create the diffgram
            if (!bUseSchema)
                ds.WriteXml(writer, XmlWriteMode.DiffGram);
            else
            {
                XmlSerializer ser = new XmlSerializer(typeof(DataSet));
                ser.Serialize(writer, ds);
            }

            // Show the saved data
            writer.Close();
            StreamReader reader = new StreamReader(fileName);
            OutputText.Text = reader.ReadToEnd();
            reader.Close();
            RefreshWebBrowser();
        }

        // **********************************************************
        // Filling the checked listbox
        private void DiffGram_Load(object sender, EventArgs e)
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


        // **********************************************************
        // Check all the elements of the listbox
        private void ButtonCheckAll_Click(object sender, System.EventArgs e)
        {
            for (int i = 0; i < ColumnSettings.Items.Count; i++)
                ColumnSettings.SetItemChecked(i, true);
        }
        // **********************************************************

        // **********************************************************
        // Uncheck all the elements of the listbox
        private void ButtonUncheckAll_Click(object sender, System.EventArgs e)
        {
            for (int i = 0; i < ColumnSettings.Items.Count; i++)
                ColumnSettings.SetItemChecked(i, false);
        }
        // **********************************************************

        // **********************************************************
        // Open the child form to edit the current DataSet
        private void ButtonEdit_Click(object sender, System.EventArgs e)
        {
            Edit ef = new Edit();
            ef.DataInstance = m_data;
            ef.ShowDialog();

            SaveData(m_data, true, Check_WithSchema.Checked);
        }
        // **********************************************************

        // **********************************************************
        // Toggle view mode
        private void ViewAsWeb_CheckedChanged(object sender, System.EventArgs e)
        {
            if (ViewAsWeb.Checked == true)
            {
                object o1 = null, o2 = null, o3 = null, o4 = null;
              
                WebBrowser.Navigate(Url, ref o1, ref o2, ref o3, ref o4);
                OutputText.Visible = false;
                WebBrowser.Visible = true;
            }
            else
            {
                OutputText.Visible = true;
                WebBrowser.Visible = false;
            }
        }
        // **********************************************************

        // **********************************************************
        // Refresh the WebBrowser
        private void RefreshWebBrowser()
        {
            object o1 = null, o2 = null, o3 = null, o4 = null;
            WebBrowser.Navigate(Url, ref o1, ref o2, ref o3, ref o4);
        }
        // **********************************************************





    }
}