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
    public partial class Factories : Form
    {
        public Factories()
        {
            InitializeComponent();
        }

        private void Factories_Load(object sender, EventArgs e)
        {
            DataTable providers = DbProviderFactories.GetFactoryClasses();
            provList.DataSource = providers;
        }
    }
}