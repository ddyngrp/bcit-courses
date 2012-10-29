using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using System.Xml;
using System.Data.OleDb;

namespace XMLdotNET.XMLDataReader
{
    public partial class TestXMLDataReader : Form
    {
        public TestXMLDataReader()
        {
            InitializeComponent();
        }

        private void ButtonLoadData_Click(object sender, EventArgs e)
        {
            // Execute the command
            string nwind = "PROVIDER=sqloledb;SERVER=www.j2ee.ca;UID=aspx;password=aspx;DATABASE=northwind;";
            string query = "SELECT employeeid, firstname, lastname, title FROM employees";
            OleDbConnection conn = new OleDbConnection(nwind);
            OleDbCommand cmd = new OleDbCommand(query, conn);

            // Create the XML data reader
            conn.Open();
            OleDbDataReader dr = cmd.ExecuteReader();
            XmlDataReader reader = new XmlDataReader(dr);
            ProcessDataReader(reader);
            reader.Close();
            conn.Close();
        }

        private void ProcessDataReader(XmlReader reader)
        {
            ResultsListBox.Items.Clear();
            while (reader.Read())
            {
                ResultsListBox.Items.Add(reader.ReadOuterXml());
                //MessageBox.Show(reader.ReadOuterXml());
            }
            reader.Close();
        }


    }
}