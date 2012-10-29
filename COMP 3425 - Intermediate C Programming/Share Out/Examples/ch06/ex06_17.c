/* ex06_17.c */
/* What does this program do? */
#include <stdio.h>
#define SIZE 10

int whatIsThis( const int b[], int p ); /* function prototype */

/* function main begins program execution */
int main( void )
{
   int x; /* holds return value of function whatIsThis */

   /* initialize array a */
   int a[ SIZE ] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

   x = whatIsThis( a, SIZE );

   printf( "Result is %d\n", x );

   return 0; /* indicates successful termination */

} /* end main */

/* what does this function do? */
int whatIsThis( const int b[], int p )
{
   /* base case */
   if ( p == 1 ) {
      return b[ 0 ];
   } /* end if */
   else { /* recursion step */ 

      return b[ p - 1 ] + whatIsThis( b, p - 1 );
   } /* end else */
   
} /* end function whatIsThis */



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

