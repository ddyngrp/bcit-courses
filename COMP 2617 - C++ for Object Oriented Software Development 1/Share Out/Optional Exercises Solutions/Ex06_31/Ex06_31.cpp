// Exercise 6.31 Solution: Ex06_31.cpp
// Reverse the digits of a number.
#include <iostream>
using std::cin; 
using std::cout; 
using std::endl; 

#include <iomanip> 
using std::setw;

int reverseDigits( int ); // function prototype

int main()
{
   int number; // input number

   cout << "Enter a number between 1 and 9999: ";
   cin >> number;

   cout << "The number with its digits reversed is: ";

   // find number with digits reversed
   cout << reverseDigits( number ) << endl;
   return 0; // indicate successful termination
} // end main

// reverseDigits returns number obtained by reversing digits of n
int reverseDigits( int n )
{
   int reverse = 0; // reversed number
   int divisor = 1000; // current divisor
   int multiplier = 1; // current multiplier

   // loop until single-digit number
   while ( n > 9 ) 
   {
      // if n >= current divisor, determine digit
      if ( n >= divisor ) 
      {
         // update reversed number with current digit
         reverse += n / divisor * multiplier;
         n %= divisor; // update n
         divisor /= 10; // update divisor
         multiplier *= 10; // update multiplier
      } // end if
      else // else, no digit
         divisor /= 10; // update divisor
   } // end while
   
   reverse += n * multiplier;
   return reverse; // return reversed number
} // end function reverseDigits

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
