/* ex03_30.c 
   What does this program print? */
#include <stdio.h>

/* function main begins program execution */
int main( void )
{
   int row = 10; /* initialize row */
   int column;   /* define column */

   while ( row >= 1 ) { /* loop until row < 1 */
      column = 1;       /* set column to 1 as interation begins */

      while ( column <= 10 ) {               /* loop 10 times */
         printf( "%s", row % 2 ? "<": ">" ); /* output */
         column++;                           /* increment column */
      } /* end inner while */

      row--;          /* decrement row */
      printf( "\n" ); /* begin new output line */
   } /* end outer while */

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

