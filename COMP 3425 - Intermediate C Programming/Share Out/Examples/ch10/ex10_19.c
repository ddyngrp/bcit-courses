/* ex10_19.c */
/* This program determines if a value is a multiple of X. */
#include <stdio.h>

int multiple( int num ); /* prototype */

int main( void )
{ 
   int y; /* y will hold an integer entered by the user  */

   printf( "Enter an integer between 1 and 32000: " );
   scanf( "%d", &y );

   /* if y is a multiple of X */
   if ( multiple( y ) ) {
      printf( "%d is a multiple of X\n", y );
   } /* end if */
   else {
      printf( "%d is not a multiple of X\n", y );
   } /* end else */

   return 0; /* indicates successful termination */
} /* end main */

/* determine if num is a multiple of X */
int multiple( int num )
{ 
   int i;        /* counter */
   int mask = 1; /* initialize mask */
   int mult = 1; /* initialize mult */

   for ( i = 1; i <= 10; i++, mask <<= 1 ) {
      
      if ( ( num & mask ) != 0 ) { 
         mult = 0;
         break;
      } /* end if */

   } /* end for */

   return mult;
} /* end function multiple */


 

/**************************************************************************
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
