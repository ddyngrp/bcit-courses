/* ex10_20.c */
#include <stdio.h>

int mystery( unsigned bits ); /* prototype */

int main( void )
{ 
   unsigned x; /* x will hold an integer entered by the user */

   printf( "Enter an integer: " );
   scanf( "%u", &x );

   printf( "The result is %d\n", mystery( x ) );
   
   return 0; /* indicates successful termination */
} /* end main */

/* What does this function do? */
int mystery( unsigned bits )
{ 
   unsigned i;              /* counter */
   unsigned mask = 1 << 31; /* initialize mask */
   unsigned total = 0;      /* initialize total */

   for ( i = 1; i <= 32; i++, bits <<= 1 ) {

      if ( ( bits & mask ) == mask ) { 
         total++;
      } /* end if */

   } /* end for */

   return !( total % 2 ) ? 1 : 0;
} /* end function mystery */


 

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
