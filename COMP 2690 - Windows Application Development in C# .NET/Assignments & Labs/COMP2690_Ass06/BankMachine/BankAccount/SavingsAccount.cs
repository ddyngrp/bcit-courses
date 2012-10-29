using System;
using System.Collections.Generic;
using System.Text;

namespace BankMachine
{
    /// <summary>
    /// Represents a savings account.
    /// </summary>
    public class SavingsAccount : BankAccount
    {
        /// <summary>
        /// Creates a new savings account.
        /// </summary>
        /// <param name="openingAccountBalance">Initial balance for the account.</param>
        public SavingsAccount(decimal openingAccountBalance) : base(openingAccountBalance)
        {
        }

        /// <summary>
        /// Returns whether this account has enough money to perform the transaction.
        /// </summary>
        /// <param name="amount">Amount to check against the account.</param>
        /// <returns>True or false depending on the account balance.</returns>
        public override bool HasSufficientFunds(decimal amount)
        {
            if (base.Balance >= amount)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /// <summary>
        /// Returns a string representation of the account.
        /// </summary>
        public override string ToString()
        {
            String returnString = "Savings " + base.AccountNumber.ToString();

            return returnString;
        }
    }
}
