// Fig. 18.8: Record.cs
// Serializable class that represents a data record.
using System;
using System.Collections.Generic;
using System.Text;

public class Record
{
    private int account;
    private string firstName;
    private string lastName;
    private decimal balance;

    // parameterless constructor sets members to default values
    public Record()
        : this(0, "", "", 0.0M)
    {
    } // end constructor

    // overloaded constructor sets members to parameter values
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
} // end class Record


