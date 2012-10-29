// Fig. 6.13: fig06_13.cpp
// square function used to demonstrate the function 
// call stack and activation records.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void square( int *); // prototype for function square

int main()
{
   int a = 10; // value to square (local automatic variable in main)

   cout << a << " squared: "; //display original a
   square( &a );
   cout << a << endl; // display a squared

   return 0; // indicate successful termination
} // end main

// returns the square of an integer
void square( int * xPtr ) // x is a local variable
{
   *xPtr *= *xPtr; // calculate square and modify object pointer is pointing to
} // end function square



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
