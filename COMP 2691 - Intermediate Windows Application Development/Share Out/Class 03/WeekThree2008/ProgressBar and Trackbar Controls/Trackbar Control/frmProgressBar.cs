using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Trackbar_Control
{
    public partial class frmProgressBar : Form
    {
        public frmProgressBar()
        {
            InitializeComponent();
        }

        private void tmrTimer_Tick(object sender, EventArgs e)
        {
            if (prgIndicator.Value < prgIndicator.Maximum)
                // Increase the ProgressBar indicator
                prgIndicator.Value += 5;
            else
                // Reset the ProgressBar indicator
                prgIndicator.Value = prgIndicator.Minimum;

            lblMessage.Text = "Percentage Complete: " + prgIndicator.Value + "%";

        }

        private void trkSpeed_Scroll(object sender, EventArgs e)
        {
            TrackBar trkSpeed = (TrackBar)sender;
            if (trkSpeed.Value >= 1)
                // Set timer value based on user's selection
                tmrTimer.Interval = trkSpeed.Value;
        }

        private void vScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            textBox1.Text= vScrollBar1.Value.ToString();
        }

        
    }
}