using System;
using System.Collections.Generic;
using System.Text;

namespace BankMachine
{
    /// <summary>
    /// This exception is thrown when there are insufficient funds.
    /// </summary>
    public class NoSufficientFundsException : ApplicationException
    {
        private BankAccount account;
        private Transaction transaction;

        /// <summary>
        /// Creates a new exception with a message.
        /// </summary>
        /// <param name="account">The account that has insufficient funds.</param>
        /// <param name="transaction">The transaction that provoked the error.</param>
        public NoSufficientFundsException(BankAccount account, Transaction transaction)
            : base("There are not sufficient funds to perform this transaction.")
        {
            this.account = account;
            this.transaction = transaction;
        }

        /// <summary>
        /// Returns the account that doesn't have the funds.
        /// </summary>
        public BankAccount Account
        {
            get
            { return this.account; }
        }

        /// <summary>
        /// Returns the transaction being performed on the account.
        /// </summary>
        public Transaction Transaction
        {
            get { return this.transaction; }
        }

    }
}
