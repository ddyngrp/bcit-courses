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
        public PiCalculator()
        {
            InitializeComponent();
        }

        private void CalcPi(int digits)
        {
            StringBuilder pi = new StringBuilder("3", digits + 2);

            if (digits > 0)
            {
                pi.Append(".");

                for (int i = 0; i < digits; i += 9)
                {
                    int nineDigits = NineDigitsofPi.StartingAt(i + 1);
                    int digitCount = Math.Min(digits - i, 9);
                    String ds = String.Format("{0:D9}", nineDigits);
                    pi.Append(ds.Substring(0, digitCount));
                    _pi.Text = pi.ToString();
                }
            }
        }

        private void _calcButton_Click(object sender, EventArgs e)
        {
            CalcPi((int)_digits.Value);
        }
    }
}
