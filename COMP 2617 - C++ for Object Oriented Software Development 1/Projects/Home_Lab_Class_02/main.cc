// Steffen L. Norgren, A00683006
//
// Home Lab Class 02 - Question 3.14: main.cc
// ---------------------------------------------------------------------


#include <iostream>

// Our standard using statements
using std::cout;
using std::endl;

#include "Employee.h" // Including the header file

int main()
{
	// Create a couple objects
	Employee employee1( "Steffen", "Norgren", static_cast< int >(100) * 1.10 );
	Employee employee2( "Lars", "Norgren", static_cast< int >(1000) * 1.10 );
	
	// Display the results
	cout << employee1.getFirstName() << " " <<
		employee1.getLastName() << " $" <<
		employee1.getSalary() << "\n" << endl;
	
	cout << employee2.getFirstName() << " " <<
		employee2.getLastName() << " $" <<
		employee2.getSalary() << "\n" << endl;
	
	return 0; // Success!	
}
