// Steffen L. Norgren, A00683006
//
// Home Lab Class 02 - Question 3.14: Employee.cc
// ---------------------------------------------------------------------


#include <iostream>

// Our standard using statements
using std::cout;
using std::endl;

#include "Employee.h" // including the definitions for Employee class

// Constructor initializes first/last name and salary
Employee::Employee( string name1, string name2, int income )
{
	setFirstName( name1 );
	setLastName( name2 );
	setSalary( income );
}

// Functions that set the aforementioned data
void Employee::setFirstName( string name1 )
{
	FirstName = name1;
}

void Employee::setLastName( string name2 )
{
	LastName = name2;
}

void Employee::setSalary( int income )
{
	if ( income < 0 ) // setting the salary to 0 if it is negative
		Salary = 0;
	else
		Salary = income;
}

// Functions that get the aforementioned data
string Employee::getFirstName()
{
	return FirstName;
}

string Employee::getLastName()
{
	return LastName;
}

int Employee::getSalary()
{
	return Salary;
}
