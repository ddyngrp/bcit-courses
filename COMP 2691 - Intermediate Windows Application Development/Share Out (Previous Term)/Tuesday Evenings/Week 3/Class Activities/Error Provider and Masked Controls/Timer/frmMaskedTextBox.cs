using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Timer
{
    public partial class frmMaskedTextBox : Form
    {
        public frmMaskedTextBox()
        {
            InitializeComponent();
        }

        private void frmMaskedTextBox_Load(object sender, EventArgs e)
        {
            maskedTextBox1.Mask = "00/00/0000";
            maskedTextBox1.MaskInputRejected += new MaskInputRejectedEventHandler(maskedTextBox1_MaskInputRejected);


            // Other code
            maskedTextBox1.ValidatingType = typeof(System.DateTime);
            maskedTextBox1.TypeValidationCompleted += new TypeValidationEventHandler(maskedTextBox1_TypeValidationCompleted);


        }
        void maskedTextBox1_MaskInputRejected(object sender, MaskInputRejectedEventArgs e)
        {
            toolTip1.ToolTipTitle = "Invalid Input";
            toolTip1.Show("We're sorry, but only digits (0-9) are allowed in dates.", maskedTextBox1, maskedTextBox1.Location, 5000);
        }

        public void maskedTextBox1_TypeValidationCompleted(object sender, TypeValidationEventArgs e)
        {
            if (!e.IsValidInput)
            {
                toolTip1.ToolTipTitle = "Invalid Date Value";
                toolTip1.Show("We're sorry, but the value you entered is not a valid date. Please change the value.", maskedTextBox1, 5000);
                e.Cancel = true;
            }
        }


    }
}