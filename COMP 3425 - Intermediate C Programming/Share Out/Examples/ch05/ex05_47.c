/* ex05_47.c */
/* What does this program do? */
#include <stdio.h>

int mystery( int a, int b ); /* function prototype */
 
/* function main begins program execution */  
int main( void )
{
   int x; /* first integer */
   int y; /* second integer */
   
   printf( "Enter two integers: " );
   scanf( "%d%d", &x, &y );

   printf( "The result is %d\n", mystery( x, y ) );
   
   return 0; /* indicates successful termination */

} /* end main */

/* Parameter b must be a positive integer 
   to prevent infinite recursion */
int mystery( int a, int b )
{
   /* base case */
   if ( b == 1 ) {
      return a;
   } /* end if */
   else { /* recursive step */
      return a + mystery( a, b - 1 );
   } /* end else */
   
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