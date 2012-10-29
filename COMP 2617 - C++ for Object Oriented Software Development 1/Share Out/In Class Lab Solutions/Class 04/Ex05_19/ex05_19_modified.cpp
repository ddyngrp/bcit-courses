// Exercise 5.19 Solution: ex05_19.cpp
// Approximate value for pi.

// Modified program to ask user how many multiples of 10 million terms to calculate.
// Also displays # of seconds to calculate solution.
// Also, will only display intermediate result every 10 million terms
//       instead of every 50 terms.

// BTW, the actual value of pi to 14 places after the 
//       decimal point is 3.14159265358979

#include <iostream> 
using std::cout; 
using std::cin;
using std::endl; 
using std::fixed; // fixed decimal notation

#include <iomanip> // parameterized stream manipulators
using std::setprecision; // sets numeric output precision
using std::setw;

#include <time.h> // required to calculate time to do calculations

int main()
{
   long double pi = 0.0;    // approximated value for pi 
   long double denom = 1.0; // denominator of current term
   long long accuracy;      // number of million terms to calculate

   time_t startTime, endTime, totalTime;  // used to calculate time

   // Ask user how many million terms to calculate
   cout << "How many multiples of 10 million terms should be calculated? ";
   cin >> accuracy;
   cout << endl;

   //Convert to actual #
   accuracy *= 10000000; // multiply by 10 million

   // set floating-point number format
   cout << fixed << setprecision( 14 );

   startTime = time(NULL);

   // loop through each term
   for ( long long loop = 1; loop <= accuracy; loop++ ) 
   {
      if ( loop % 2 != 0 ) // if odd-numbered term, add current term
         pi += 4.0 / denom;
      else // if even-numbered term, subtract current term
         pi -= 4.0 / denom;

	  denom += 2.0; // update denominator

      // display number of terms and 
      // approximated value for pi with 10 digits of precision
	  // if multiple of 50 term
      if( loop % 10000000 == 0 )
		  cout << setw(6) << loop/10000000 << " 10 million terms =" << setw(19) << pi << '\n'; 

   } // end for

   //Calculate and output # of seconds to do calculations
   endTime = time(NULL);
   totalTime = endTime - startTime;
   cout << "\n\n" << "The time required to calculate the solution was " << totalTime << " seconds.\n" << endl;
   
   system("pause");
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