using System;
using System.Collections.Generic;
using System.Text;

namespace BankMachine
{
    /// <summary>
    /// Represents a deposit transaction.
    /// </summary>
    public class DepositTransaction : Transaction
    {
        private BankAccount account;

        /// <summary>
        /// Creates a new deposit transaction.
        /// </summary>
        /// <param name="account">Account to which to make a depost.</param>
        /// <param name="amount">Deposit amount.</param>
        public DepositTransaction(BankAccount account, decimal amount) : base(amount)
        {
            this.account = account;
        }

        /// <summary>
        /// Performs the transaction and checks for the following exceptions in this order:
        /// 1. Checks if account is active.
        /// 2. Checks if the transaction amount is greater than zero.
        /// 3. Checks if the account has enough funds.
        /// </summary>
        /// <returns>The status of the transaction.</returns>
        public override TransactionStatus DoTransaction()
        {
            if (!this.account.Active)
            {
                throw new AccountInactiveException(this.account);
            }
            else if (base.Amount <= 0)
            {
                throw new InvalidTransactionAmtException(this);
            }
            else
            {
                base.setStatus(TransactionStatus.Pending);
            }

            return base.Status;
        }

        /// <summary>
        /// Sets the status of the transaction to complete once 30 seconds has passed.
        /// </summary>
        /// <returns>The status of the transaction.</returns>
        public override TransactionStatus Process()
        {
            if (DateTime.Now.Subtract(base.Date).Seconds >= 30)
            {
                this.account.Credit(base.Amount);
                base.setStatus(TransactionStatus.Complete);
            }

            return base.Status;
        }

        /// <summary>
        /// Returns the details of the transaction.
        /// </summary>
        public override string Details
        {
            get
            {
                return string.Format("\tAccount: {0}\r\n\tAmount: {1:C}\r\n",
                    this.account.AccountNumber, base.Amount);
            }
        }

        /// <summary>
        /// Returns the transaction type.
        /// </summary>
        public override string TransactionType
        {
            get { return "Deposit"; }
        }
    }
}
