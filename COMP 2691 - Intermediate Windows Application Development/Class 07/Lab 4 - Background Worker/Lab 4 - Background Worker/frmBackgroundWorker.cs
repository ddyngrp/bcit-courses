using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Threading
{
    public partial class frmBackgroundWorker : Form
    {
        DateTime startDateTime = DateTime.Now;

        public frmBackgroundWorker()
        {
            InitializeComponent();
        }

        private DataTable getDataTable(int Rows)
        {
            Threading.GetDataHelper getData = new GetDataHelper();
            return (getData.getDataSetCities(Rows).Tables[0]);
        }

        private void frmBackgroundWorker_Activated(object sender, EventArgs e)
        {
            backgroundWorker1.RunWorkerAsync();
            timer1.Start();
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            DataTable dt;
            toolStripStatusLabel1.Text = "Loading ... " + "Thanks for your patience";
            dt = getDataTable(1000000);
            e.Result = dt;
            toolStripStatusLabel1.Text = "Please, wait ...";
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            TimeSpan ts = DateTime.Now.Subtract(startDateTime);
            string sTime = "  ..." + ts.Minutes.ToString("00") +
                               ":" + ts.Seconds.ToString("00") +
                               ":" + ts.Milliseconds.ToString("000");

            toolStripStatusTime.Text = sTime;
            if (toolStripProgressBar1.Value == toolStripProgressBar1.Maximum)
            {
                toolStripProgressBar1.Value = 0;
            }
            toolStripProgressBar1.PerformStep();
        }

        private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            toolStripProgressBar1.Value = 100;
            dataGridViewCities.DataSource = e.Result;
            toolStripStatusLabel1.Text = "";
            toolStripProgressBar1.Value = 0;
            timer1.Stop();
            toolStripStatusTime.Text = "";
        }
    }
}