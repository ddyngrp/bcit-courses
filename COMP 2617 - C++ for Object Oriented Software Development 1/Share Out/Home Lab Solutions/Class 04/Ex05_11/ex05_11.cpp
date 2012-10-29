// Exercise 5.11 Solution: ex05_11.cpp
// Calculating compound interest with several interest rates.
#include <iostream> 
using std::cout; 
using std::endl; 
using std::fixed; // fixed decimal notation

#include <iomanip> // parameterized stream manipulators
using std::setprecision; // sets numeric output precision

#include <cmath> // math functions
using std::pow; // enables program to use function pow

int main()
{
   double amount; // amount on deposit
   double principal = 1000.0; // starting principal

   // set floating-point number format
   cout << fixed << setprecision( 2 );

   // loop through interest rates 5% to 10%
   for ( int rate = 5; rate <= 10; rate++ ) 
   {
      // display table headers
      cout << "Interest Rate: " << rate << "%" 
         << "\nYear\tAmount on deposit\n";

      // calculate amount on deposit for each of ten years
      for ( int year = 1; year <= 10; year++ ) 
      {
         // calculate new amount for specified year
         amount = principal * pow( 1 + ( rate / 100.0 ), year );

         // output one table row
         cout << year << '\t' << amount << '\n';
      } // end for
   
      cout << '\n';
   } // end for

   cout << endl;
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