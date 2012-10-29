/* Exercise 10.10 Solution */
#include <stdio.h>
#include <stdlib.h>

void displayBits( unsigned value ); /* prototype */

int main()
{ 
   unsigned val; /* value from user */
   
   /* prompt user and read value */
   printf( "Enter an integer: " );
   scanf( "%u", &val ); 
   
   /* display value before shifting */
   printf( "\n%u before right shifting 4 bits is:\n", val );
   displayBits( val );

   /* display value after shifting */
   printf( "\n%u after right shifting 4 bits is:\n", val );
   displayBits( val >> 4 );

   printf("\n"); // to improve looks of output

   system("pause");  // wait until user signals completion

   return 0; /* indicate successful termination */

} /* end main */

/* function displayBits prints each bit of value */
void displayBits( unsigned value )
{ 
   unsigned c; /* bit counter */
   unsigned displayMask = 1 << 31; /* bit mask */
   
   printf( "%7u = ", value );
   
   /* loop through bits */
   for ( c = 1; c <= 32; c++ ) { 
      value & displayMask ? putchar( '1' ) : putchar( '0' );
      value <<= 1; /* shift value 1 bit to the left */
      
      if ( c % 8 == 0 ) { /* print a space */
         putchar( ' ' );
      } /* end if */

   } /* end for */
   
   putchar( '\n' );
} /* end function displayBits */




 /*************************************************************************
 * (C) Copyright 1992-2004 by Deitel & Associates, Inc. and               *
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
