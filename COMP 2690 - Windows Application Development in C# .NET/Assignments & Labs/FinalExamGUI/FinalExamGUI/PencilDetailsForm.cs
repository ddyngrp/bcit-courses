using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using FinalExam;

namespace FinalExamGUI
{
    public partial class PencilDetailsForm : Form
    {
        private MechanicalPencil mechPencil;

        public PencilDetailsForm(MechanicalPencil mechPencil)
        {
            InitializeComponent();
            this.mechPencil = mechPencil;
        }

        private void PencilDetailsForm_Load(object sender, EventArgs e)
        {
            this.btnOK.Select();
            this.txtLeadType.Select();

            txtLeadType.Text = this.mechPencil.LeadType;
            txtLeadCapacity.Text = this.mechPencil.LeadCapacity.ToString();
            txtColour.Text = this.mechPencil.Color;
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            int leadCapacity;

            try
            {
                int.TryParse(txtLeadCapacity.Text, out leadCapacity);

                this.mechPencil.LeadType = txtLeadType.Text;
                this.mechPencil.Color = txtColour.Text;

                if (!int.TryParse(txtLeadCapacity.Text, out leadCapacity))
                {
                    MessageBox.Show("Please enter a numeric lead capacity.", "Error",
                        MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                }
                else
                {
                    this.mechPencil.LeadCapacity = leadCapacity;
                    this.DialogResult = DialogResult.OK;
                }
            }
            catch (LeadTypeException exception)
            {
                MessageBox.Show(exception.Message, "Error",
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
            catch (LeadCapacityException exception)
            {
                MessageBox.Show(exception.Message, "Error",
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
        }
    }
}