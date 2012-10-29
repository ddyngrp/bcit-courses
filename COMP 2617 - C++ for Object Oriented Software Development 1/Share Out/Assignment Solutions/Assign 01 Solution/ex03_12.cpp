// Assignment 1 Solution: ex03_12.cpp
// Create and manipulate Account objects.
// 
// Bob Langelaan
// Oct. 13, 2006

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

// include definition of class Account from Account.h
#include "Account.h"

// function main begins program execution
int main()
{
   Account account1( 50 ); // create Account object
   Account account2( 25 ); // create Account object

   Account account3( -25 ); // attempt to initialize to negative amount;

   // display initial balance of each object
   cout << "account1 balance: $" << account1.getBalance() << endl;
   cout << "account2 balance: $" << account2.getBalance() << endl;

   int depositAmount; // stores deposit amount read from user

   cout << "\nEnter deposit amount for account1: "; // prompt
   cin >> depositAmount; // obtain user input

   cout << "\ndeposit " << depositAmount 
      << " into account1 balance\n\n";
   account1.credit( depositAmount ); // add to account1

   // display balances
   cout << "account1 balance: $" << account1.getBalance() << endl;
   cout << "account2 balance: $" << account2.getBalance() << endl;

   cout << "\nEnter deposit amount for account2: "; // prompt
   cin >> depositAmount; // obtain user input

   cout << "\ndeposit " << depositAmount 
      << " into account2 balance\n\n";
   account2.credit( depositAmount ); // add to account2

   // display balances
   cout << "account1 balance: $" << account1.getBalance() << endl;
   cout << "account2 balance: $" << account2.getBalance() << endl;

   int withdrawalAmount; // stores withdrawal amount read from user

   cout << "\nEnter withdrawal amount for account1: "; // prompt
   cin >> withdrawalAmount; // obtain user input

   cout << "\nattempting to subtract " << withdrawalAmount 
      << " from account1 balance\n\n";
   account1.debit( withdrawalAmount ); // try to subtract from account1

   // display balances
   cout << "account1 balance: $" << account1.getBalance() << endl;
   cout << "account2 balance: $" << account2.getBalance() << endl;

   cout << "\nEnter withdrawal amount for account2: "; // prompt
   cin >> withdrawalAmount; // obtain user input

   cout << "\nattempting to subtract " << withdrawalAmount 
      << " from account2 balance\n\n";
   account2.debit( withdrawalAmount ); // try to subtract from account2

   // display balances
   cout << "account1 balance: $" << account1.getBalance() << endl;
   cout << "account2 balance: $" << account2.getBalance() << endl;

   system("pause"); // To allow us to view the output before the console window dissappears

   return 0; // indicate successful termination

} // end main
