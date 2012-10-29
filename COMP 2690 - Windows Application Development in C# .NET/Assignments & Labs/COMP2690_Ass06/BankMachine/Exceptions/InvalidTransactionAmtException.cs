using System;
using System.Collections.Generic;
using System.Text;

namespace BankMachine
{
    /// <summary>
    /// This exception is thrown when a transaction is attempted without a positive value.
    /// </summary>
    public class InvalidTransactionAmtException : ApplicationException
    {
        private Transaction transaction;

        /// <summary>
        /// Creates a new exception with a message.
        /// </summary>
        /// <param name="transaction">The transaction being performed.</param>
        public InvalidTransactionAmtException(Transaction transaction)
            : base("Invalid transaction amount. Amount must be greater than $0.00")
        {
            this.transaction = transaction;
        }

        /// <summary>
        /// Returns the transaction being performed.
        /// </summary>
        public Transaction Transaction
        {
            get { return this.transaction; }
        }
    }
}
