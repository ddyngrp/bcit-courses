using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WeekThree
{
    public partial class dateTimePickerDropOff : Form
    {
        public dateTimePickerDropOff()
        {
            InitializeComponent();
        }

        private void dateTimePicker1_ValueChanged(object sender, EventArgs e)
        {
            DateTime dropOffDate = dateTimePicker1.Value;

            // add extra time when items are dropped off around Sunday
            if (dropOffDate.DayOfWeek == DayOfWeek.Friday ||
               dropOffDate.DayOfWeek == DayOfWeek.Saturday ||
               dropOffDate.DayOfWeek == DayOfWeek.Sunday)

                //estimate three days for delivery
                outputLabel.Text = dropOffDate.AddDays(3).ToLongDateString();
            else
                // otherwise estimate only two days for delivery
                outputLabel.Text = dropOffDate.AddDays(2).ToLongDateString();

        }

        private void dateTimePickerDropOff_Load(object sender, EventArgs e)
        {
            // user cannot select days before today
            dateTimePicker1.MinDate = DateTime.Today;

            // user can only select days of this year
            dateTimePicker1.MaxDate = DateTime.Today.AddYears(1);

        }
    }
}