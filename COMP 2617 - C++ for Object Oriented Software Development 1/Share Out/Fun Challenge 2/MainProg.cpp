// Assign 5 Main Program - used to "test drive" the Fraction class
// File Name: MainProg.cpp
// Author: Bob Langelaan
// Date: Feb. 18th, 2006

#include <iostream>
 using std::cout; 
 using std::endl; 
 using std::cin; 
 using std::ios;

#include <iomanip> 
 using std::setw; 
 using std::setprecision; 
 using std::setiosflags;

#include "Fraction.h" // include definition of modified Fraction class

int main()
{
   Fraction term_count = 1;  // the # of terms computed so far
		
   Fraction	e = 1,	// contains the series sum
			term = 1, // contains the term value
		    x = 5;		    // the value for which e**x is to be computed	


   int count  = 1;
   while ( count < 15 ) {
	   term *= x;
	   term /= term_count;
	   e += term;
	   term_count += Fraction(1);
	   ++count;
	   cout << "\nThe numerator = " << e.getNum() << " ; The denominator = " << e.getDenom();
   }

   long long num = e.getNum();
   long long denom = e.getDenom();
   double e_float = static_cast<double> (num) / static_cast<double> (denom);

   // Now output the computed series sum

   cout << setiosflags( ios::fixed | ios::showpoint )
        << setprecision( 2 ) << "\n\ne raised to the " << 5 << " power is "
        << setprecision( 10 ) << e_float << endl;

   // Output how many terms needed to get to required accuracy

   cout << "\nThe number of terms computed is "
	    << count << '\n' << endl;

   cout << '\n' << endl;

   return 0;

} // end main

