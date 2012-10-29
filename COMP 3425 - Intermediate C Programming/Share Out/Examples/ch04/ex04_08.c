/* ex04_08.c 
   What does this program print? */
#include <stdio.h>

/* function main begins program execution */
int main( void )
{
   int x; 
   int y;
   int i; 
   int j; 

   /* prompt user for input */
   printf( "Enter two integers in the range 1-20: " );
   scanf( "%d%d", &x, &y ); /* read values for x and y */

   for ( i = 1; i <= y; i++ ) { /* count from 1 to y */

      for ( j = 1; j <= x; j++ ) { /* count from 1 to x */
         printf( "@" ); /* output @ */
      } /* end inner for */

      printf( "\n" ); /* begin new line */
   } /* end outer for */

   return 0; /* indicate program ended successfully */

} /* end function main */



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