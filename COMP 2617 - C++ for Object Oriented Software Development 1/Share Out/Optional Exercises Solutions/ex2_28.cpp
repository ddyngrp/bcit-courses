// Exercise 2.28 Solution
#include <iostream> // allows program to perform input and output

using std::cout; // program uses cout
using std::endl; // program uses endl
using std::cin; // program uses cin

int main()
{
   int number; // integer read from user

   cout << "Enter a five-digit integer: "; // prompt
   cin >> number; // read integer from user

   cout << number / 10000 << "   ";
   number = number % 10000;
   cout << number / 1000 << "   ";
   number = number % 1000;
   cout << number / 100 << "   ";
   number = number % 100;
   cout << number / 10 << "   ";
   number = number % 10;
   cout << number << endl;

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