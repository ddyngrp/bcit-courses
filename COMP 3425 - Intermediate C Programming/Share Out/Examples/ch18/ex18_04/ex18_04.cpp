// Exercise 18.4 Solution: Ex18_04.cpp
// Inline function that calculates the volume of a sphere.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <cmath>
using std::pow;

const double PI = 3.14159; // define global constant PI

// calculates volume of a sphere
inline double sphereVolume( const double radius ) 
{ 
   return 4.0 / 3.0 * PI * pow( radius, 3 ); 
} // end inline function sphereVolume

int main()
{
   double radiusValue;

   // prompt user for radius 
   cout << "Enter the length of the radius of your sphere: ";
   cin >> radiusValue; // input radius 

   // use radiusValue to calculate volume of sphere and display result
   cout << "Volume of sphere with radius " << radiusValue 
      << " is " << sphereVolume( radiusValue ) << endl;
   return 0; // indicates successful termination
} // end main
