/* Fig. 10.13: fig10_13.c
   Using the bitwise shift operators */
#include <stdio.h>

void displayBits( unsigned value ); /* prototype */

int main( void )
{ 
   unsigned number1 = 960; /* initialize number1 */

   /* demonstrate bitwise left shift */
   printf( "\nThe result of left shifting\n" );
   displayBits( number1 );
   printf( "8 bit positions using the " );
   printf( "left shift operator << is\n" );
   displayBits( number1 << 8 );

   /* demonstrate bitwise right shift */
   printf( "\nThe result of right shifting\n" );
   displayBits( number1 );
   printf( "8 bit positions using the " );
   printf( "right shift operator >> is\n" );
   displayBits( number1 >> 8 );

   return 0; /* indicates successful termination */
} /* end main */

/* display bits of an unsigned integer value */
void displayBits( unsigned value )
{ 
   unsigned c; /* counter */
   
   /* declare displayMask and left shift 31 bits */
   unsigned displayMask = 1 << 31;

   printf( "%7u = ", value );

   /* loop through bits */
   for ( c = 1; c <= 32; c++ ) { 
      putchar( value & displayMask ? '1' : '0' );
      value <<= 1; /* shift value left by 1 */

      if ( c % 8 == 0 ) { /* output a space after 8 bits */
         putchar( ' ' );
      } /* end if */

   } /* end for */

   putchar( '\n' );
} /* end function displayBits */




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