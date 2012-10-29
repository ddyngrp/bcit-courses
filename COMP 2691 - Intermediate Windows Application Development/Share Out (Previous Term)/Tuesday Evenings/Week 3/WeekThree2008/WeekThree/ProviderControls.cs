using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WeekThree
{
    public partial class ProviderControls : Form
    {
        public ProviderControls()
        {
            InitializeComponent();
        }

        private void ProviderControls_Load(object sender, EventArgs e)
        {
            toolTip1.SetToolTip(textBox1, "Enter the name of the product");
           // Console.WriteLine(toolTip1.GetToolTip(textBox1));

        }
    }
}