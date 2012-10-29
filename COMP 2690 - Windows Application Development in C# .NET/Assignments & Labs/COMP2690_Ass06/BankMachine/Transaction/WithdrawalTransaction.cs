using System;
using System.Collections.Generic;
using System.Text;

namespace BankMachine
{
    /// <summary>
    /// Represents a withdrawal transaction.
    /// </summary>
    public class WithdrawalTransaction : Transaction
    {
        private BankAccount account;

        /// <summary>
        /// Create a new withdrawal.
        /// </summary>
        /// <param name="account">Account from which to withdrawal.</param>
        /// <param name="amount">Amount to withdrawal from the account.</param>
        public WithdrawalTransaction(BankAccount account, decimal amount) : base(amount)
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
            else if (!this.account.HasSufficientFunds(base.Amount))
            {
                throw new NoSufficientFundsException(this.account, this);
            }
            else
            {
                this.account.Debit(base.Amount);
                base.setStatus(TransactionStatus.Complete);
            }

            return base.Status;
        }

        /// <summary>
        /// Returns the status of thr transaction.
        /// </summary>
        public override TransactionStatus Process()
        {
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
            get { return "Withdrawal"; }
        }
    }
}
