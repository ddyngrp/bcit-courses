// Fig 17.8: fig17_08.c
// Assigning elements of an array in C89
#include <stdio.h>

int main( void )
{
   int i; // declare loop counter
   int a[ 5 ]; // array declaration
   
   a[ 0 ] = 1; // explicitly assign values to array elements...
   a[ 4 ] = 2; // after declaration of array
   
   // assign zero to all elements but the first and last
   for ( i = 1; i < 4; i++ ) 
      a[ i ] = 0;
      
    // output array contents
   printf( "The array is \n" );
   for ( i = 0; i < 5; i++ )
      printf( "%d\n", a[ i ] );
   
   return 0; // indicates successful termination
} // end main


 /*************************************************************************
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
 *************************************************************************/
