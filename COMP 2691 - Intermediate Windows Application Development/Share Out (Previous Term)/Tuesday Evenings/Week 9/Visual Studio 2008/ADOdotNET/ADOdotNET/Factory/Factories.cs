using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Data.Common;

namespace ADOdotNET.Factory
{
    public partial class Factories : Form
    {
        public Factories()
        {
            InitializeComponent();
        }

        private void Factories_Load(object sender, EventArgs e)
        {
            // GetFactoryClasses returns a DataTable that contains information about all installed
            // providers that implement DbProviderFactory.
            DataTable providers = DbProviderFactories.GetFactoryClasses();
            provList.DataSource = providers;
        }
    }
}