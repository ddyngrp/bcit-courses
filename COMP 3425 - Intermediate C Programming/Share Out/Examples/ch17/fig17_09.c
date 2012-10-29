// Fig 17.9: fig17_09.c
// Using C99 designated initializers
// to initialze the elements of an array in C99
#include <stdio.h>

int main( void )
{
   int a[5] = 
   {
      [ 0 ] = 1, // initialize elements with designated initializers
      [ 4 ] = 2 // within the declaration of the array
   };
    
   // output array contents
   printf( "The array is \n" );
   for ( int i = 0; i < 5; i++ )
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

