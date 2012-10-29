/* Exercise 10.12 Solution */
#include <stdio.h>
#include <stdlib.h>

/* prototypes */
void displayBits( unsigned value );
unsigned power2( unsigned n, unsigned p );

int main()
{ 
   unsigned number; /* value from user */
   unsigned pow;    /* number of bits to left shift */
   unsigned result; /* result of shift */

   /* prompt user and read two integers */
   printf( "Enter two integers: " );
   scanf( "%u%u", &number, &pow ); 
   
   /* display bits of number */
   printf( "\nnumber:\n" );
   displayBits( number );

   /* display bits of pow */
   printf( "\npow:\n" );
   displayBits( pow );

   /* perform shift and display results */
   result = power2( number, pow );
   printf( "\n%u * 2^%u = %u\n", number, pow, result );
   displayBits( result );

   printf("\n");     // output blank line for appearances

   system("pause");  // wait until user signals completion

   return 0; /* indicate successful termination */

} /* end main */

/* function power2 left shifts n by p */
unsigned power2( unsigned n, unsigned p )
{ 
   return n << p;

} /* end function power2 */

/* display the bits of value */
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
