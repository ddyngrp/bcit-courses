// Fig. 18.1: fig18_01.cpp
// Addition program that displays the sum of two numbers.
#include <iostream> // allows program to perform input and output

int main()
{
   int number1; // first integer to add

   std::cout << "Enter first integer: "; // prompt user for data
   std::cin >> number1; // read first integer from user into number1

   int number2; // second integer to add
   int sum; // sum of number1 and number2

   std::cout << "Enter second integer: "; // prompt user for data
   std::cin >> number2; // read second integer from user into number2
   sum = number1 + number2; // add the numbers; store result in sum
   std::cout << "Sum is " << sum << std::endl; // display sum; end line

   return 0; // indicate that program ended successfully
} // end function main



/**************************************************************************
 * (C) Copyright 1992-2007 by Deitel & Associates, Inc. and               *
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
