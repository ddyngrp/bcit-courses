using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BankLibrary
{
    public class Record
    {
        private int account;
        private string firstName;
        private string lastName;
        private decimal balance;

        public Record()
            : this(0, "", "", 0.0M)
        {
        } // end constructor

        public Record(int accountValue, string firstNameValue,
            string lastNameValue, decimal balanceValue)
        {
            Account = accountValue;
            FirstName = firstNameValue;
            LastName = lastNameValue;
            Balance = balanceValue;
        } // end constructor
        
        // property that gets and sets Account
        public int Account
        {
            get
            {
                return account;
            } // end get
            set
            {
                account = value;
            } // end set
        } // end property Account

        // property that gets and sets FirstName
        public string FirstName
        {
            get
            {
                return firstName;
            } // end get
            set
            {
                firstName = value;
            } // end set
        } // end property FirstName

        // property that gets and sets LastName
        public string LastName
        {
            get
            {
                return lastName;
            } // end get
            set
            {
                lastName = value;
            } // end set
        } // end property LastName

        // property that gets and sets Balance
        public decimal Balance
        {
            get
            {
                return balance;
            } // end get
            set
            {
                balance = value;
            } // end set
        } // end property Balance
    }
}
