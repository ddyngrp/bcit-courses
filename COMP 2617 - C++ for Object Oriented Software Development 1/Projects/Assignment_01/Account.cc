// Steffen L. Norgren, A00683006
//
// Assignment 01 - Exercise 3.12 Solution: Account.hh
// ---------------------------------------------------------------------
// Create and manipulate Account objects.

#include <iostream>
using std::cout;
using std::endl;

// include definition of class Account from Account.h
#include "Account.h"


// Constructor initializes account balences
Account::Account( int balance )
{
	setBalance( balance );
}

// Set the balance for the account
void Account::setBalance( int balance)
{
	if ( balance < 0 ) // Return an error if initial balance is negative
		cout << "Error: Initial balance cannot be negative.\n" << endl;
	else
		accountBalance = balance;
}

// Add the deposit amount to the account
void Account::credit( int deposit )
{
	if ( deposit < 0 ) // Return an error if credit is negative
		cout << "Error: Credit amount cannot be negative.\n" << endl;
	else
		accountBalance = getBalance() + deposit;
}

// Subtract the withdrawal amount from the account
void Account::debit( int withdrawal )
{
	if ( withdrawal < 0 ) // Return an error if debit is negative
		cout << "Error: Debit amount cannot be negative.\n" << endl;
	else
		if ( withdrawal > getBalance() )
			cout << "Debit amount exceeds account balance.\n" << endl;
		else
			accountBalance = getBalance() - withdrawal;
}

// Return the balance
int Account::getBalance()
{
	return accountBalance;
}
