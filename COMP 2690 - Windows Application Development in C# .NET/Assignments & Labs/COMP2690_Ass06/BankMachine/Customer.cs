using System;
using System.Collections.Generic;
using System.Text;

namespace BankMachine
{
    /// <summary>
    /// This class holds customer account and transaction information.
    /// </summary>
    public class Customer
    {
        private BankAccountCollection accounts;
        private TransactionCollection transactionHistory;

        /// <summary>
        /// Creates a new customer, which holds account and transaction information.
        /// </summary>
        /// <param name="accounts">The accounts for this customer.</param>
        public Customer(BankAccountCollection accounts)
        {
            this.accounts = accounts;
            this.transactionHistory = new TransactionCollection();
        }

        /// <summary>
        /// Returns the customer's collection of bank accounts.
        /// </summary>
        public BankAccountCollection Accounts
        {
            get { return this.accounts; }
        }

        /// <summary>
        /// Returns the customer's transaction history collection.
        /// </summary>
        public TransactionCollection TransactionHistory
        {
            get { return this.transactionHistory; }
        }
    }
}
