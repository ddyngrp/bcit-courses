// Exercise 4.13 Solution: Gas.cpp
// Member-function definitions for class Gas that calculates 
// average mpg with sentinel-controlled repetition.
#include <iostream>
using std::cin; 
using std::cout; 
using std::endl; 
using std::fixed;

#include "Gas.h" // include definition of class Gas from Gas.h

// function to calculate average mpg
void Gas::calculateMPG()
{
   double gallons; // gallons used for current tank
   double miles; // miles driven for current tank
   double totalGallons = 0; // total gallons used
   double totalMiles = 0; // total miles driven

   double milesPerGallon; // miles per gallon for tankful
   double totalMilesPerGallon; // miles per gallon for trip

   // processing phase
   // get miles used for first tank
   cout << "Enter the miles used (-1 to quit): ";
   cin >> miles;
   cout << fixed; // set floating-point number format

   // exit if the input is -1 otherwise, proceed with the program
   while ( miles != -1 )
   {
      // prompt user for gallons and obtain the input from user
      cout << "Enter gallons: ";
      cin >> gallons;

      // add gallons and miles for this tank to total
      totalMiles += miles;
      totalGallons += gallons;

      // calculate miles per gallon for the current tank
      if ( gallons != 0 )
      {
         milesPerGallon =  miles / gallons;
         cout << "MPG this tankful: " << milesPerGallon;            
      } // end if 

      // calculate miles per gallon for the total trip
      if ( totalGallons != 0 )
      {
         totalMilesPerGallon = totalMiles / totalGallons;
         cout << "\nTotal MPG: " << totalMilesPerGallon;
      } // end if 

      // prompt user for new value for miles
      cout << "\n\nEnter the miles used (-1 to quit): ";
      cin >> miles;
   } // end while       
} // end function calculateMPG

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