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
    public partial class MainForum : Form
    {
        private Customer customer;

        public MainForum()
        {
            InitializeComponent();
        }

        private void MainForum_Load(object sender, EventArgs e)
        {
            // Create a new accounts collection
            BankAccountCollection accounts = new BankAccountCollection();

            // Add accounts to the accounts collection
            accounts.Add(new SavingsAccount(0));
            accounts.Add(new SavingsAccount(0));
            accounts.Add(new LineOfCreditAccount(0, 10000));

            // Create a new customer with the accounts collection
            this.customer = new Customer(accounts);
            
            lstAccounts.DataSource = customer.Accounts;
        }

        private void btnDeposit_Click(object sender, EventArgs e)
        {
            // Creates a new dialog window
            DepositForm dlg = new DepositForm(customer, lstAccounts.SelectedIndex);
            dlg.ShowDialog();

            // Closes the dialog window
            dlg.Dispose();
        }

        private void btnWithdraw_Click(object sender, EventArgs e)
        {
            // Creates a new dialog window
            WithdrawForm dlg = new WithdrawForm(customer, lstAccounts.SelectedIndex);
            dlg.ShowDialog();

            // Closes the dialog window
            dlg.Dispose();
        }

        private void btnTransfer_Click(object sender, EventArgs e)
        {
            // Creates a new dialog window
            TransferForm dlg = new TransferForm(customer, lstAccounts.SelectedIndex);
            dlg.ShowDialog();

            // Closes the dialog window
            dlg.Dispose();
        }

        private void btnBalance_Click(object sender, EventArgs e)
        {
            // Creates a new dialog window
            BalanceForm dlg = new BalanceForm(customer, lstAccounts.SelectedIndex);
            dlg.ShowDialog();

            // Closes the dialog window
            dlg.Dispose();
        }

        private void btnTransactionHistory_Click(object sender, EventArgs e)
        {
            // Creates a new dialog window
            TransactionHistoryForm dlg = new TransactionHistoryForm(customer.TransactionHistory);
            dlg.ShowDialog();

            // Closes the dialog window
            dlg.Dispose();
        }

        private void lstAccounts_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void transactionTimer_Tick(object sender, EventArgs e)
        {
            // Process pending transactions every 5000 milliseconds (5 seconds)
            customer.TransactionHistory.ProcessPendingTransactions();
        }
    }
}