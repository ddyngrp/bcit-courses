using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WeekThree
{
    public partial class LinkLabel : Form
    {
        public LinkLabel()
        {
            InitializeComponent();
        }

        private void driveLinkLabel_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start(@"C:\");
        }

        private void BCITlinkLabel_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            BCITlinkLabel.LinkVisited = true;
            // change LinkColor after it has been clicked
            System.Diagnostics.Process.Start("IExplore", "http://www.bcit.ca");

        }

        private void linkLabel3_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("calc");
        }
    }
}