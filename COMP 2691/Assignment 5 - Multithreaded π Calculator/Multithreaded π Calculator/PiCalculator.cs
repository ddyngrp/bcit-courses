using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Multithreaded_π_Calculator
{
    public partial class PiCalculator : Form
    {
        PiObject pi;

        public PiCalculator()
        {
            InitializeComponent();
        }

        private void CalcPi(BackgroundWorker bw, int digits)
        {
        }

        private void _calcButton_Click(object sender, EventArgs e)
        {
            if (this._calcButton.Text == "Calculate")
            {
                timer1.Start();

                pi = new PiObject
                {
                    calcValue = "",
                    digits = (int)_digits.Value,
                    progress = 0
                };
                backgroundWorker1.RunWorkerAsync(pi);
                progressBar1.Maximum = pi.digits;
                _calcButton.Text = "Cancel";
            }
            else
            {
                timer1.Stop();

                backgroundWorker1.CancelAsync();
                _calcButton.Text = "Calculate";
            }
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            PiObject piObj = e.Argument as PiObject;
            BackgroundWorker bw = sender as BackgroundWorker;
            StringBuilder pi = new StringBuilder("3", piObj.digits + 2);

            if (piObj.digits > 0)
            {
                pi.Append(".");

                for (int i = 0; i < piObj.digits; i += 9)
                {
                    if (!this.backgroundWorker1.CancellationPending)
                    {
                        int nineDigits = NineDigitsofPi.StartingAt(i + 1);
                        int digitCount = Math.Min(piObj.digits - i, 9);
                        String ds = String.Format("{0:D9}", nineDigits);
                        pi.Append(ds.Substring(0, digitCount));
                        piObj.calcValue = pi.ToString();
                        piObj.progress = i + 1;
                    }
                    else
                    {
                        e.Cancel = true;
                    }
                }
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            _pi.Text = pi.calcValue;
            progressBar1.Value = pi.progress;
        }

        private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            this._calcButton.Text = "Calculate";

            if (e.Cancelled)
            {
                this._pi.Text = pi.calcValue + " <<cancelled>>";
            }
        }
    }

    class PiObject
    {
        public String calcValue { get; set; }
        public int digits { get; set; }
        public int progress { get; set; }
    }
}
