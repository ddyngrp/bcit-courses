/*

Program Name: Assign1P2.c

Author: Bob Langelaan

Problem Description:

Write a program that converts integer Fahrenheit temperatures from 
-40 to 212 degrees to floating-point Celsius temperatures with 3 
digits of precision.  Use the formula:

celsius = 5.0 / 9.0 * ( fahrenheit - 32 );

to perform the calculation.  The output should be printed in two right
justified columns of 10 characters each, and the Celsius temperatures
should be preceded by a sing for both positive and negative values.

*/
#include <stdio.h>
#include <stdlib.h>

#define START_VALUE -40
#define END_VALUE 212

int main( void )
{ 
   int iFahrenheit; /* holds fahrenheit temperature */
   double dCelsius; /* holds celsius temperature */
   
   printf( "%10s%12s\n\n", "Fahrenheit", "celsius" );
   
   /* convert fahrenheit to celsius and display temperatures
      showing the sign for celsius temperatures */
   for ( iFahrenheit = START_VALUE; iFahrenheit <= END_VALUE; iFahrenheit++ ) { 
      dCelsius = 5.0 / 9.0 * ( iFahrenheit - 32 );
      printf( "%10d%+12.3f\n", iFahrenheit, dCelsius );
   } /* end for */

   printf("\n");
   system("pause");
   return 0; /* indicate successful termination */

} /* end main */
