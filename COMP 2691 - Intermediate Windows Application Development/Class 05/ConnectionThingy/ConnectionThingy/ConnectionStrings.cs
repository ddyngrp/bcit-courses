using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.Data.SqlClient;
using System.Data.OleDb;

using System.Configuration;

namespace ConnectionThingy
{
    public partial class ConnectionStrings : Form
    {
        public ConnectionStrings()
        {
            InitializeComponent();
        }

        private void btnGetData_Click(object sender, EventArgs e)
        {
            String strConn = @"Server=XENOWIN\SQLEXPRESS;"
                             + "Provider=SQLOLEDB;"
                             + "database=Northwind;"
                             + "uid=ironix;"
                             + "password=trustno1;";

            // For OLEDB Provider
            OleDbConnection conn = new OleDbConnection(strConn);

            conn.Open();
        }

        private void btnConfigString_Click(object sender, EventArgs e)
        {
            String connString = ConfigurationManager.ConnectionStrings["XenoConnect"].ConnectionString;

            // For SQL Provider
            SqlConnection conn = new SqlConnection(connString);

            conn.Open();
        }

        private void btnRunQuery_Click(object sender, EventArgs e)
        {
            String connString = ConfigurationManager.ConnectionStrings["XenoConnect"].ConnectionString;

            // For SQL Provider
            SqlConnection conn = new SqlConnection(connString);

            conn.Open();

            SqlCommand cmd = new SqlCommand(txtQuery.Text, conn);

            SqlDataAdapter adapter = new SqlDataAdapter(cmd);

            DataSet ds = new DataSet();

            adapter.Fill(ds, "Customers");

            dataGridView.DataSource = ds.Tables["Customers"];

            conn.Close();

            //SqlConnectionStringBuilder myBuilder = new SqlConnectionStringBuilder();
        }
    }
}
