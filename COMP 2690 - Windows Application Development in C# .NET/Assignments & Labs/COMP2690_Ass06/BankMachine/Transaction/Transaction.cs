using System;
using System.Collections.Generic;
using System.Text;

namespace BankMachine
{
    /// <summary>
    /// Represents a bank transaction that can involve multiple accounts.
    /// </summary>
    public abstract class Transaction
    {
        private decimal amount;
        private TransactionStatus status;
        private DateTime transactionDate;

        /// <summary>
        /// Creates a new transaction.
        /// </summary>
        /// <param name="amount">Amount of the transaction.</param>
        public Transaction(decimal amount)
        {
            this.amount = amount;
            this.transactionDate = DateTime.Now;
            this.status = TransactionStatus.Pending; // all transactions are pending to begin with
        }

        /// <summary>
        /// Performs the transaction.
        /// </summary>
        /// <returns>The status of the transaction.</returns>
        public abstract TransactionStatus DoTransaction();

        /// <summary>
        /// Processes the transaction and determines whether it can be completed.
        /// </summary>
        /// <returns></returns>
        public abstract TransactionStatus Process();

        /// <summary>
        /// Sets the status of the transaction.
        /// </summary>
        /// <param name="newStatus">Status for the transaction.</param>
        protected void setStatus(TransactionStatus newStatus)
        {
            this.status = newStatus;
        }

        /// <summary>
        /// Returns the amount of the transaction.
        /// </summary>
        public decimal Amount
        {
            get { return this.amount; }
        }

        /// <summary>
        /// Returns the date of the transaction.
        /// </summary>
        public DateTime Date
        {
            get { return this.transactionDate; }
        }

        /// <summary>
        /// Returns the details of the transaction.
        /// </summary>
        public abstract string Details { get; }

        /// <summary>
        /// Returns the transaction status.
        /// </summary>
        public TransactionStatus Status
        {
            get { return this.status; }
        }

        /// <summary>
        /// Returns a summary of the transaction.
        /// </summary>
        public string Summary
        {
            get
            {
                String pendingStatus = "";

                if (this.status == TransactionStatus.Pending)
                {
                    pendingStatus = "(Pending)";
                }

                return string.Format("{0:yyyy-MM-dd} {1} {2:#.##}",
                    this.transactionDate, this.TransactionType, pendingStatus);
            }
        }

        /// <summary>
        /// Returns the transaction type.
        /// </summary>
        public abstract string TransactionType { get; }
    }
}
