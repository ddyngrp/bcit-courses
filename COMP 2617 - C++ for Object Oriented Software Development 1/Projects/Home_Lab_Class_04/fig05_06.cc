// Steffen L. Norgren, A00683006
//
// Assignment 03 - Exercise 5.11 Solution: fig05_06.cc
// ---------------------------------------------------------------------

#include <iostream>
using std::cout;
using std::endl;
using std::fixed;

#include <iomanip>
using std::setw; // enables program to set a field width
using std::setprecision;

#include <cmath> // standard C++ math library
using std::pow; // enables program to use function pow

int main()
{
	double amount; // amount on deposit at end of each year
	double principal = 1000.0; // initial amount before interest

	// set floating-point number format
	cout << fixed << setprecision( 2 );

	// Vary the interest rate from 5% to 10%
	for ( double rate = 0.05; rate <= 0.10; rate += 0.01 )
	{
		// display headers
		cout << "Using an interest rate of " << rate * 100 << "%" << endl;
		cout << "Year" << setw( 21 ) << "Amount on deposit" << endl;

		// calculate amount on deposit for each of ten years
		for ( int year = 1; year <= 10; year++ )
		{
			// calculate new amount for specified year
			amount = principal * pow( 1.0 + rate, year );

			// display the year and the amount
			cout << setw( 4 ) << year << setw( 21 ) << amount << endl;
		} // end for 
		
		cout << endl;
	}

   return 0; // indicate successful termination
} // end main


/**************************************************************************
 * (C) Copyright 1992-2005 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
