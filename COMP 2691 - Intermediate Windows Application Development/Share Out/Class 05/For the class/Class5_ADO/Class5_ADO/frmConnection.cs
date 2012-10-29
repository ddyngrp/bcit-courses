using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using System.Data.OleDb;      // For generic code
using System.Data.SqlClient;  // For SQL data provider

using System.Configuration;   // To read from App.Config



namespace Class5_ADO
{
    public partial class frmConnection : Form
    {
        public frmConnection()
        {
            InitializeComponent();
        }

        private void btnGetData_Click(object sender, EventArgs e)
        {

            String strConn = "Server=www.j2ee.ca;Provider=SQLOLEDB;";
            strConn += "database=northwind;";
            strConn += "uid=aspx;password=aspx;";

            // For OLEDB provider
            OleDbConnection conn = new OleDbConnection(strConn);

            conn.Open();




        }

        private void btnConnectionStringfromConfig_Click(object sender, EventArgs e)
        {
            string connString = ConfigurationManager.ConnectionStrings["J2EEConnect"].ConnectionString;

            // For SQL Provider
            SqlConnection conn = new SqlConnection(connString);
            conn.Open();

        }
    }
}
