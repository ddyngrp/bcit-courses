/*
 * PiCalculator.cs - Assignment Five - Multithreaded π Calculator
 * 
 * Copyright (C) Steffen L. Norgren 2009 <ironix@trollop.org>
 *               A00683006
 *               
 * Created: 2009-07-22
 * 
 * PiCalculator.cs is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * PiCalculator.cs is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

        /// <summary>
        /// Default constructor
        /// </summary>
        public PiCalculator()
        {
            InitializeComponent();
        }

        /// <summary>
        /// The calculate/cancel button event
        /// </summary>
        /// <param name="sender">Reference to the object that raised the event</param>
        /// <param name="e">Provides data for a cancelable event</param>
        private void _calcButton_Click(object sender, EventArgs e)
        {
            if (this._calcButton.Text == "Calculate")
            {
                timer1.Start();

                // Just a simple object to hold some values to be accessed globally
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

        /// <summary>
        /// Our main worker thread. This is the main loop that calculates Pi
        /// </summary>
        /// <param name="sender">Reference to the object that raised the event</param>
        /// <param name="e">Provides data for a cancelable event</param>
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

        /// <summary>
        /// Background worker completion event
        /// </summary>
        /// <param name="sender">Reference to the object that raised the event</param>
        /// <param name="e">Provides data for a cancelable event</param>
        private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            this._calcButton.Text = "Calculate";

            if (e.Cancelled)
            {
                this._pi.Text = pi.calcValue + " <<cancelled>>";
            }
        }
    }

    /// <summary>
    /// Simple object to hold Pi values
    /// </summary>
    class PiObject
    {
        public String calcValue { get; set; }
        public int digits { get; set; }
        public int progress { get; set; }
    }
}
