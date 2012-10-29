using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace GUIConceptsPart2.ADONetSamples.Async
{
    public partial class NonBlocking : Form
    {
        public NonBlocking()
        {
            InitializeComponent();
        }

        private void btnExecute_Click(object sender, EventArgs e)
        {
            string connString = "Async=true;SERVER=(local);DATABASE=northwind;UID=sa;";

            using (SqlConnection conn = new SqlConnection(connString))
            {
                SqlCommand cmd = new SqlCommand("SELECT lastname,firstname FROM employees", conn);
                conn.Open();
                IAsyncResult iar = cmd.BeginExecuteReader();

                // Do something here

                SqlDataReader reader = (SqlDataReader)cmd.EndExecuteReader(iar);
                ProcessData(reader);
            }
        }
        protected void ProcessData(SqlDataReader reader)
        {
            StringBuilder sb = new StringBuilder("");
            while (reader.Read())
                sb.AppendFormat("{0}, {1} \n", reader[0], reader[1]);

            reader.Close();

            Results.Text = sb.ToString();
        }
    }
}