using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace GUI_Mockup
{
    public partial class CommAudio : Form
    {
        public CommAudio()
        {
            InitializeComponent();
            download.Enabled = false;
        }

        private void connectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!serverToolStripMenuItem.Checked)
            {
                new Connect().Show();
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void seToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (serverToolStripMenuItem.Checked)
            {
                serverToolStripMenuItem.Checked = false;
            }
            seToolStripMenuItem.Checked = true;
            removeFile.Enabled = false;
            addFile.Enabled = false;
            groupBox1.Enabled = false;
            download.Enabled = true;
        }

        private void serverToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (seToolStripMenuItem.Checked)
            {
                seToolStripMenuItem.Checked = false;
            }
            serverToolStripMenuItem.Checked = true;
            removeFile.Enabled = true;
            addFile.Enabled = true;
            groupBox1.Enabled = true;
            download.Enabled = false;
        }
    }
}
