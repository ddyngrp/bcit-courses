/* ex06_18.c */
#include <stdio.h>
#define SIZE 10

/* function prototype */
void someFunction( const int b[], int startIndex, int size ); 

/* function main begins program execution */
int main( void )
{
   int a[ SIZE ] = { 8, 3, 1, 2, 6, 0, 9, 7, 4, 5 }; /* initialize a */
  
   printf( "Answer is:\n" );
   someFunction( a, 0, SIZE );
   printf( "\n" );

   return 0; /* indicates successful termination */

} /* end main */

/* What does this function do? */
void someFunction( const int b[], int startIndex, int size )
{
   if ( startIndex < size ) {
      someFunction( b, startIndex + 1, size );
      printf( "%d  ", b[ startIndex ] );
   } /* end if */

} /* end function someFunction */


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

