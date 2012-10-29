using System;
using System.Collections.Generic;
using System.Text;

namespace BankMachine
{
    /// <summary>
    /// Represents a line of credit account.
    /// </summary>
    public class LineOfCreditAccount : BankAccount
    {
        private decimal overdraftLimit;

        /// <summary>
        /// Creates a new line of credit (overdraft) account with a specified credit limit.
        /// </summary>
        /// <param name="openingAccountBalance">Initial balance for the account.</param>
        /// <param name="overdraftLimit">Overdraft limit for the account.</param>
        public LineOfCreditAccount(decimal openingAccountBalance, decimal overdraftLimit)
            : base(openingAccountBalance)
        {
            this.overdraftLimit = overdraftLimit;
        }

        /// <summary>
        /// Returns whether this account has enough money to perform the transaction.
        /// </summary>
        /// <param name="amount">Amount to check against the account.</param>
        /// <returns>True or false depending on the account balance.</returns>
        public override bool HasSufficientFunds(decimal amount)
        {
            if ((base.Balance + this.overdraftLimit) >= amount)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /// <summary>
        /// Returns the overdraft limit of the current account.
        /// </summary>
        public decimal OverDraftLimit
        {
            get { return this.overdraftLimit; }
        }

        /// <summary>
        /// Returns a string representation of the account.
        /// </summary>
        public override string ToString()
        {
            String returnString = "Line of credit " + base.AccountNumber.ToString();

            return returnString;
        }
    }
}
