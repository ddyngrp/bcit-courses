using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Timer
{
    public partial class frmErrorProvider : Form
    {
        public frmErrorProvider()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // Assign a ToolTip to the TextBox1 control.
           
          

        }

        private void button1_Click(object sender, EventArgs e)
        {
            // Assume it's OK to close the form.
            this.DialogResult = DialogResult.OK;
            // Clear all error icons.
            errorProvider1.SetError(txtProduct, "");
            errorProvider1.SetError(txtQty, "");
            // Check that first field contains something.
            if (txtProduct.Text == "")
            {
                errorProvider1.SetError(txtProduct, "Must enter a product name");
                this.DialogResult = DialogResult.None;
            }

            try
            {
                // Attempt to get a valid quantity in second field.
                int qty = Convert.ToInt32(txtQty.Text);
                // Throw a generic error if out of range.
                if (qty < 1 || qty > 100) throw new Exception(); 
            }
            catch
            {
                // Regardless of the exception type, use the same error message
                errorProvider1.SetError(txtQty, "Enter a valid number in range 1-100");
                this.DialogResult = DialogResult.None;
            }
            // Close the form only if validation passed.
            // (This line is not really required if this is a dialog box.)
            if (this.DialogResult == DialogResult.OK) this.Close();
            
        }
    }
    
}