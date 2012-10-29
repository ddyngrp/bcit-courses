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
    public partial class TransactionHistoryForm : Form
    {
        private TransactionCollection transactions;

        public TransactionHistoryForm(TransactionCollection transactions)
        {
            InitializeComponent();
            this.transactions = transactions;
        }

        private void TransactionHistoryForm_Load(object sender, EventArgs e)
        {
            // Populate the transaction history
            PopulateTransactions();

            // This will close the dialog.
            this.btnClose.Select();
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            // This will close the dialog.
            this.btnClose.Select();
        }
        
        private void chkShowDetails_CheckedChanged(object sender, EventArgs e)
        {
            PopulateTransactions();
        }

        private void PopulateTransactions()
        {
            txtTransactionHistory.Clear();

            if (chkShowDetails.Checked)
            {
                // Loop through all the transactions and append each to the text box.
                foreach (Transaction transaction in transactions)
                {
                    txtTransactionHistory.AppendText(transaction.Summary + "\r\n");
                    txtTransactionHistory.AppendText(transaction.Details + "\r\n");
                }
            }
            else
            {
                // Loop through all the transactions and append each to the text box.
                foreach (Transaction transaction in transactions)
                {
                    txtTransactionHistory.AppendText(transaction.Summary + "\r\n");
                }
            }
        }
    }
}