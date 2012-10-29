// Steffen L. Norgren, A00683006
//
// Assignment 01 - Exercise 3.12 Solution: Account.hh
// ---------------------------------------------------------------------
// Create and manipulate Account objects.

#include <iostream>
using std::cout;
using std::endl;

// Including and using the string class
#include <string>
using std::string;

// Account Class Definition
class Account
{
	public: // Public declarations for Account.cc
		Account( int );
		void setBalance( int );
		int getBalance();
		void credit( int );
		void debit( int );	
	private: // Declaring a private variable for Account.cc
		int accountBalance;
};
