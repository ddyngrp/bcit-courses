// Assignment 1 Solution: Account.h
// Definition of Account class.
// 
// Bob Langelaan
// Oct. 13, 2006

class Account
{
public:
   Account( int ); // constructor initializes balance
   void credit( int ); // add an amount to the account balance
   void debit( int ); // subtract an amount from the account balance
   int getBalance(); // return the account balance
private:
   int balance; // data member that stores the balance
}; // end class Account

