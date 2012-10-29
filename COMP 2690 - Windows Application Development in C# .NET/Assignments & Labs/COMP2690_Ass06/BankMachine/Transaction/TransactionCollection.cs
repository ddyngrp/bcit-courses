using System;
using System.Collections.Generic;
using System.Text;

namespace BankMachine
{
    /// <summary>
    /// Holds a collection of transactions.
    /// </summary>
    public class TransactionCollection : List<Transaction>
    {
        private List<Transaction> TransactionPending = new List<Transaction>();

        /// <summary>
        /// Adds the transaction to the collection unless it is a pending transaction.
        /// In that case it will be added to a transaction pending collection as well,
        /// which will be processed periodically.
        /// </summary>
        /// <param name="transaction">Transaction to add.</param>
        public void Add(Transaction transaction)
        {
            if (transaction.Status == TransactionStatus.Pending)
            {
                this.TransactionPending.Add(transaction);
            }

            base.Add(transaction);
        }

        /// <summary>
        /// Loop through all the pending transactions and call their process methods.
        /// </summary>
        public void ProcessPendingTransactions()
        {
            for (int i = 0; i < this.TransactionPending.Count; i++ )
            {
                if (this.TransactionPending[i].Process() == TransactionStatus.Complete)
                {
                    this.TransactionPending.RemoveAt(i);
                }
            }
        }
    }
}
