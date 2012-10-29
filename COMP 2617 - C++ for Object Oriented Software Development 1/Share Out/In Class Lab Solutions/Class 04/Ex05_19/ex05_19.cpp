// Exercise 5.19 Solution: ex05_19.cpp
// Approximate value for pi.

// When only calculating 1000 terms, result is only correct to
//   2 places after the decimal place (3.14)
#include <iostream> 
using std::cout; 
using std::endl; 
using std::fixed; // fixed decimal notation

#include <iomanip> // parameterized stream manipulators
using std::setprecision; // sets numeric output precision

int main()
{
   long double pi = 0.0; // approximated value for pi 
   long double denom = 1.0; // denominator of current term
   long accuracy = 1000; // number of terms

   // Change "accuracy" above to 2 million instead of 1000 to get
   //   6 digits correct after the decimal place (3.141592)

   // set floating-point number format
   cout << fixed << setprecision( 10 );

   // display table headers
   cout << "Accuracy set at: " << accuracy << "\n\nterm\t\tpi\n";

   // loop through each term
   for ( long loop = 1; loop <= accuracy; loop++ ) 
   {
      if ( loop % 2 != 0 ) // if odd-numbered term, add current term
         pi += 4.0 / denom;
      else // if even-numbered term, subtract current term
         pi -= 4.0 / denom;

      // display number of terms and 
      // approximated value for pi with 8 digits of precision
	  // if multiple of 50 term
      if( loop % 50 == 0 )
		  cout << loop << "\t\t" << pi << '\n';

      denom += 2.0; // update denominator
   } // end for

   cout << endl;
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