using System;
using System.Collections.Generic;
using System.Text;

namespace BankMachine
{
    /// <summary>
    /// Represents transfer transaction.
    /// </summary>
    public class TransferFundsTransaction : Transaction
    {
        private BankAccount sourceAccount;
        private BankAccount destinationAccount;

        /// <summary>
        /// Creates a new transaction.
        /// </summary>
        /// <param name="sourceAccount">Source account to debit from.</param>
        /// <param name="destinationAccount">Destination account to credit to.</param>
        /// <param name="amount">Transfer amount.</param>
        public TransferFundsTransaction(BankAccount sourceAccount, BankAccount destinationAccount, decimal amount)
            : base(amount)
        {
            this.sourceAccount = sourceAccount;
            this.destinationAccount = destinationAccount;
        }

        /// <summary>
        /// Performs the transaction. Checks the following conditions in this order:
        /// 1. Checks if the source and destination accounts are the same.
        /// 2. Checks if account is active.
        /// 3. Checks if the transaction amount is greater than zero.
        /// 4. Checks if the account has enough funds.
        /// </summary>
        /// <returns>The status of the transaction.</returns>
        public override TransactionStatus DoTransaction()
        {
            if (this.sourceAccount.AccountNumber == this.destinationAccount.AccountNumber)
            {
                throw new TransferFundsException();
            }
            else if (!this.sourceAccount.Active)
            {
                throw new AccountInactiveException(this.sourceAccount);
            }
            else if (!this.destinationAccount.Active)
            {
                throw new AccountInactiveException(this.destinationAccount);
            }
            else if (base.Amount <= 0)
            {
                throw new InvalidTransactionAmtException(this);
            }
            else if (!this.sourceAccount.HasSufficientFunds(base.Amount))
            {
                throw new NoSufficientFundsException(this.sourceAccount, this);
            }
            else
            {
                this.sourceAccount.Debit(base.Amount);
                this.destinationAccount.Credit(base.Amount);
                base.setStatus(TransactionStatus.Complete);
            }

            return base.Status;
        }

        /// <summary>
        /// Returns the status of the transaction.
        /// </summary>
        /// <returns>The transaction status.</returns>
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
                return string.Format("\tFrom account {0}\r\n\tTo account {1}\r\n\tAmount: {2:C}\r\n",
                    this.sourceAccount.AccountNumber, this.destinationAccount.AccountNumber, base.Amount);
            }
        }

        /// <summary>
        /// Returns the transaction type.
        /// </summary>
        public override string TransactionType
        {
            get { return "Transfer Funds"; }
        }
    }
}
