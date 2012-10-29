using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Data.Common;

namespace GUIConceptsPart2.ADONetSamples.Factory
{
    public partial class CallDb : Form
    {
        public CallDb()
        {
            InitializeComponent();
        }

        private void btnRun_Click(object sender, EventArgs e)
        {
            string provider = ProviderNameBox.Text;
            string connString = ConnectionStringBox.Text;
            string commandText = CommandTextBox.Text;

            // Get the provider
            DbProviderFactory fact = DbProviderFactories.GetFactory(provider);

            // Create the connection
            DbConnection conn = fact.CreateConnection();
            conn.ConnectionString = connString;

            // Create the data adapter
            DbDataAdapter adapter = fact.CreateDataAdapter();
            adapter.SelectCommand = conn.CreateCommand();
            adapter.SelectCommand.CommandText = commandText;

            // Run the query
            DataTable table = new DataTable();
            adapter.Fill(table);

            // Shows the results
            Results.DataSource = table;
            
        }
    }
}