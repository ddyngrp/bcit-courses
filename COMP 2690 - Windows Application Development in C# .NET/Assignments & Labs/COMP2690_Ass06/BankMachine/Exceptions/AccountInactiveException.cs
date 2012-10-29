using System;
using System.Collections.Generic;
using System.Text;

namespace BankMachine
{
    /// <summary>
    /// This exception is thrown when a transaction is attempted on an inactive account.
    /// </summary>
    public class AccountInactiveException : ApplicationException
    {
        private BankAccount account;

        /// <summary>
        /// Creates a new exception with a message.
        /// </summary>
        /// <param name="account">The inactive account that was used.</param>
        public AccountInactiveException(BankAccount account)
            : base(string.Format("This account is currently inactive."))
        {
            this.account = account;
        }

        /// <summary>
        /// Returns the inactive account that was used.
        /// </summary>
        public BankAccount Account
        {
            get { return this.account; }
        }
    }
}
