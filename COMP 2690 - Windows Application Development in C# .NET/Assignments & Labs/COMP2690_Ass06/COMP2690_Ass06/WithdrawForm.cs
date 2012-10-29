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
    public partial class WithdrawForm : Form
    {
        private Customer customer;
        private int selectedAccount;
        private decimal amount;

        public WithdrawForm(Customer customer, int selectedAccount)
        {
            InitializeComponent();
            this.customer = customer;
            this.selectedAccount = selectedAccount;
        }

        private void WithdrawForm_Load(object sender, EventArgs e)
        {
            this.btnOK.Select();
            txtAmount.Select();

            lblAccount.Text = customer.Accounts[selectedAccount].ToString();
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            try
            {
                decimal.TryParse(txtAmount.Text, out amount);

                // Create a new transaction
                Transaction transaction = new WithdrawalTransaction(customer.Accounts[selectedAccount], amount);
                transaction.DoTransaction();

                // Add the transaction to the transaction history.
                this.customer.TransactionHistory.Add(transaction);

                // This will close the dialog with a positive result.
                this.DialogResult = DialogResult.OK;
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
    }
}