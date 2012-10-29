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
    public partial class BalanceForm : Form
    {
        private BankAccountCollection accounts;
        private int selectedAccount;

        public BalanceForm(Customer customer, int selectedAccount)
        {
            InitializeComponent();
            this.accounts = customer.Accounts;
            this.selectedAccount = selectedAccount;
        }

        private void BalanceForm_Load(object sender, EventArgs e)
        {
            btnClose.Select();

            lblAccount.Text = accounts[selectedAccount].ToString();

            lblBalance.Text = String.Format("{0:C}", accounts[selectedAccount].Balance);

            // Checks to see if this is a line of credit account.
            if (accounts[selectedAccount].ToString().Contains("credit"))
            {
                // Casts the account as a line of credit account.
                LineOfCreditAccount locAccount = (LineOfCreditAccount)accounts[selectedAccount];
                lblCreditLimit.Text = String.Format("Credit Limit: {0:C}", locAccount.OverDraftLimit);
            }
        }
        
        private void btnClose_Click(object sender, EventArgs e)
        {
            // This will close the dialog with a positive result.
            this.DialogResult = DialogResult.OK;
        }
    }
}