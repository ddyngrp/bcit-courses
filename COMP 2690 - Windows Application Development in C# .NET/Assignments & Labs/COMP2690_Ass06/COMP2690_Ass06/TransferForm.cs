using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using BankMachine;

namespace COMP2690_Ass06
{
    public partial class TransferForm : Form
    {
        private Customer customer;
        private int selectedAccount;
        private decimal amount;

        public TransferForm(Customer customer, int selectedAccount)
        {
            InitializeComponent();
            this.customer = customer;
            this.selectedAccount = selectedAccount;
        }

        private void TransferForm_Load(object sender, EventArgs e)
        {
            this.btnOK.Select();
            cboDestinationAccount.Select();

            lblAccount.Text = customer.Accounts[selectedAccount].ToString();
            cboDestinationAccount.DataSource = customer.Accounts;
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            try
            {
                decimal.TryParse(txtAmount.Text, out amount);

                // Create a new transaction
                Transaction transaction = new TransferFundsTransaction(customer.Accounts[selectedAccount],
                    customer.Accounts[cboDestinationAccount.SelectedIndex], amount);
                transaction.DoTransaction();

                // Add the transaction to the transaction history.
                this.customer.TransactionHistory.Add(transaction);

                // This will close the dialog with a positive result.
                this.DialogResult = DialogResult.OK;
            }
            catch (TransferFundsException exception)
            {
                MessageBox.Show(exception.Message, "Error",
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
            catch (AccountInactiveException exception)
            {
                MessageBox.Show(exception.Message, "Error",
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation);

            }
            catch (NoSufficientFundsException exception)
            {
                MessageBox.Show(exception.Message, "Error",
                    MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
            catch (InvalidTransactionAmtException exception)
            {
                // Make sure the input is numeric.
                if (!decimal.TryParse(txtAmount.Text, out amount))
                {
                    MessageBox.Show("Invalid amount. Please enter a numeric value.", "Error",
                        MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                }
                else
                {
                    MessageBox.Show(exception.Message, "Error",
                        MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                }
            }
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            // This will cancel the dialog.
            this.DialogResult = DialogResult.Cancel;
        }

        private void cboDestinationAccount_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}