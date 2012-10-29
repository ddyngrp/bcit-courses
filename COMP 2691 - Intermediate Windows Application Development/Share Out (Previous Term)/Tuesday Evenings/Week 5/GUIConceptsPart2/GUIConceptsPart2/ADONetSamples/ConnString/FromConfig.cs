using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Configuration;

namespace GUIConceptsPart2.ADONetSamples.ConnString
{
    public partial class FromConfig : Form
    {
        public FromConfig()
        {
            InitializeComponent();
        }

        private void btnGoGetData_Click(object sender, EventArgs e)
        {
            // Read the connection string from web.config--regardless it is encrypted or clear
            string connString = ConfigurationManager.ConnectionStrings["LocalNWind"].ConnectionString;

            using (SqlConnection conn = new SqlConnection(connString))
            {
                string cmdText = "SELECT * FROM customers";
                SqlCommand cmd = new SqlCommand(cmdText, conn);
                cmd.Connection.Open();
                SqlDataReader reader = cmd.ExecuteReader();


                // Not the best way to obtain data binding ...
                CustomerList.Items.Clear();
                while (reader.Read())
                    CustomerList.Items.Add(reader["companyname"].ToString());
                reader.Close();
            }
        }
    }
}