// Exercise 6.58 Solution: Ex06_58.cpp
// Finding the min using a function template.
#include <iostream>
using std::cin;
using std::cout; 
using std::endl; 

// definition of function template min that finds the smaller of 2 values
template < class T >
T min( T value1, T value2 )   
{
   if ( value1 < value2 )
      return value1;
   else
      return value2;
} // end function template min

int main()
{
   // demonstrate min with int values
   int int1; // first int value
   int int2; // second int value

   cout << "Input two integer values: ";
   cin >> int1 >> int2;

   // invoke int version of min
   cout << "The smaller integer value is: " << min( int1, int2 );

   // demonstrate min with char values
   char char1; // first char value
   char char2; // second char value

   cout << "\n\nInput two characters: ";
   cin >> char1 >> char2;

   // invoke char version of min
   cout << "The smaller character value is: " << min( char1, char2 );

   // demonstrate min with double values
   double double1; // first double value
   double double2; // second double value

   cout << "\n\nInput two double values: ";
   cin >> double1 >> double2;

   // invoke double version of min
   cout << "The smaller double value is: " << min( double1, double2 )
      << '\n' << endl;

   system ("pause");

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
