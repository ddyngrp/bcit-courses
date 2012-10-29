using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace COMP2690_Ass04
{
    /// <summary>
    /// This class handles interaction with the form.
    /// </summary>
    public partial class DateValidatorForm : Form
    {
        /// <summary>
        /// Initializes the form.
        /// </summary>
        public DateValidatorForm()
        {
            InitializeComponent();
        }

        private void DateValidator_Load(object sender, EventArgs e)
        {
        }

        /// <summary>
        /// This method is executed when the CheckDate button is pressed or the user
        /// presses enter on the keyboard.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnCheckDate_Click(object sender, EventArgs e)
        {
            if (DateValidator.Validate(txtYear.Text, txtMonth.Text, txtDay.Text))
            {
                lblValidation.Text = "Valid";
                lblValidation.ForeColor = Color.Green;
            }
            else
            {
                lblValidation.Text = "Invalid";
                lblValidation.ForeColor = Color.Red;
            }
        }
    }
}