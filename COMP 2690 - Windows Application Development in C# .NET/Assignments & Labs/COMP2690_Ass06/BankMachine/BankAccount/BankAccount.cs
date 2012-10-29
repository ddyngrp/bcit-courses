using System;
using System.Collections.Generic;
using System.Text;

namespace BankMachine
{
    /// <summary>
    /// Holds bank account information.
    /// </summary>
    public abstract class BankAccount
    {
        private int accountNumber = newAccountNumber();
        private static int nextNewAcctNum = 1001;
        private decimal balance;
        private bool active = true;
        private TransactionCollection pendingTransactions;

        /// <summary>
        /// Creates a new BankAccount instance with a specific opening balance for the account.
        /// </summary>
        /// <param name="openingAccountBalance">Balance to open the account with.</param>
        public BankAccount(decimal openingAccountBalance)
        {
            this.balance = openingAccountBalance;
            this.pendingTransactions = new TransactionCollection();
        }

        /// <summary>
        /// Credits the account the specified amount.
        /// </summary>
        /// <param name="amount">Amount to credit to the account.</param>
        public void Credit(decimal amount)
        {
            if (this.active)
            {
                this.balance += amount;
            }
        }

        /// <summary>
        /// Debits the account the specified amount, but checks to see whether the account
        /// has sufficient funds.
        /// </summary>
        /// <param name="amount">Amount to debit from the account.</param>
        public void Debit(decimal amount)
        {
            if (this.active && this.HasSufficientFunds(amount))
            {
                this.balance -= amount;
            }
        }

        /// <summary>
        /// Determines whether the account has sufficient funds.
        /// </summary>
        /// <param name="amount">Amount to check against the account.</param>
        /// <returns></returns>
        public abstract bool HasSufficientFunds(decimal amount);

        /// <summary>
        /// Increments the account number by one.
        /// </summary>
        /// <returns>Returns the new account number.</returns>
        private static int newAccountNumber()
        {
            return nextNewAcctNum++;
        }

        /// <summary>
        /// Returns the account number.
        /// </summary>
        public int AccountNumber
        {
            get { return this.accountNumber; }
        }

        /// <summary>
        /// Returns whether the account is active.
        /// </summary>
        public bool Active
        {
            get { return this.active; }
        }

        /// <summary>
        /// Returns the account balance.
        /// </summary>
        public decimal Balance
        {
            get { return this.balance; }
        }

        /// <summary>
        /// Returns the next account number to be generated.
        /// (Can't this just be deleted?)
        /// </summary>
        public static int NextNewAccountNumber
        {
            get { return nextNewAcctNum; }
        }
    }
}
