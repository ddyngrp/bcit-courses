// Exercise 4.33 Solution: Triangle2.cpp
// Member-function definitions for class Triangle2.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "Triangle2.h" // include definition of class Triangle2

// checks if three sides can form a triangle
void Triangle2::checkSides()
{
   int side1; // length of side 1
   int side2; // length of side 2
   int side3; // length of side 3
   bool isRightTriangle = false; // if sides can form right triangle

   // get values of three sides
   cout << "Enter side 1: ";
   cin >> side1;

   cout << "Enter side 2: ";
   cin >> side2;

   cout << "Enter side 3: ";
   cin >> side3;
      
   // square the sides
   int side1Square = side1 * side1;
   int side2Square = side2 * side2;
   int side3Square = side3 * side3;

   // test if sides can form a right triangle
   if ( ( side1Square + side2Square ) == side3Square )
     isRightTriangle = true;
   else if ( ( side1Square + side3Square ) == side2Square )
      isRightTriangle = true;
   else if ( ( side2Square + side3Square ) == side1Square )
      isRightTriangle = true;
      
   // display results
   if ( isRightTriangle )
      cout << "These are the sides of a right triangle." << endl;
   else 
      cout << "These do not form a right triangle." << endl;    
} // end function checkSides


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