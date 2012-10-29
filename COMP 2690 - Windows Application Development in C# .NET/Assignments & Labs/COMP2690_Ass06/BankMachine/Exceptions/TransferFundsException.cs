using System;
using System.Collections.Generic;
using System.Text;

namespace BankMachine
{
    /// <summary>
    /// This exception is thrown when the source and destination accounts are the same.
    /// </summary>
    public class TransferFundsException : ApplicationException
    {
        public TransferFundsException() : base("From account cannot be the same as the To account.")
        {
        }
    }
}
