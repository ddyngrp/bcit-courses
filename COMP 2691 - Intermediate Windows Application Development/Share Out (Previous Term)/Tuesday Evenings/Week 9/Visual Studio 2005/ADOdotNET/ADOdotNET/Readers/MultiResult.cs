using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Configuration;

namespace ADOdotNET.Readers
{
    public partial class MultiResult : Form
    {
        public MultiResult()
        {
            InitializeComponent();
        }

        private void btnGoGetData_Click(object sender, EventArgs e)
        {
            // MARS (Multiple Active Result Set)is a new feature in ado.net 2.0 and Sql Server 2005
            // that allows for multiple forward only read only result sets.

                        
            // Read the connection string from web.config--regardless it is encrypted or clear
            string connString = ConfigurationManager.ConnectionStrings["J2EENWind"].ConnectionString;
            StringBuilder sb = new StringBuilder("");

            using (SqlConnection conn = new SqlConnection(connString))
            {
                string cmdText = Query.Text;
                SqlCommand cmd = new SqlCommand(cmdText, conn);
                cmd.Connection.Open();
                SqlDataReader reader = cmd.ExecuteReader();
                do
                {
                    // Move through the first result set
                    while (reader.Read())
                    {
                        sb.AppendFormat("{0}, {1} \n", reader[0], reader[1]);
                    }                      
                    
                    // Separate result sets
                    
                    sb.Append("--------------------------------------------------\n");
                } while (reader.NextResult());

                reader.Close();
            }

            // Display results
            Results.Text = sb.ToString();
        }
    }
}