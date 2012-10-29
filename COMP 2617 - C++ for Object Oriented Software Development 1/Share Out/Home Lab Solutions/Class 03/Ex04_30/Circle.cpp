// Exercise 4.30 Solution: Circle.cpp
// Member-function definitions for class Circle.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "Circle.h" // include definition of class Circle

// calculate diameter, circumference and area of a circle
void Circle::calculate()
{
   double radius; // input radius 
   double pi = 3.14159; // value for pi

   // get radius value
   cout << "Enter the radius: ";
   cin >> radius;

   // compute and display diameter
   cout << "The diameter is " << radius * 2.0;

   // compute and display circumference 
   cout << "\nThe circumference is " << 2.0 * pi * radius;

   // compute and display area
   cout << "\nThe area is " << pi * radius * radius << endl;
} // end function calculate


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