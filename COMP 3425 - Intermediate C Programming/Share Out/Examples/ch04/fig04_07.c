/* Fig. 4.7: fig04_07.c
   Counting letter grades */
#include <stdio.h>

/* function main begins program execution */
int main( void )
{
   int grade;      /* one grade */
   int aCount = 0; /* number of As */
   int bCount = 0; /* number of Bs */
   int cCount = 0; /* number of Cs */
   int dCount = 0; /* number of Ds */
   int fCount = 0; /* number of Fs */

   printf(  "Enter the letter grades.\n"  );
   printf(  "Enter the EOF character to end input.\n"  );

   /* loop until user types end-of-file key sequence */
   while ( ( grade = getchar() ) != EOF ) {
      
      /* determine which grade was input */
      switch ( grade ) { /* switch nested in while */

         case 'A': /* grade was uppercase A */
         case 'a': /* or lowercase a */
            ++aCount; /* increment aCount */
            break; /* necessary to exit switch */

         case 'B': /* grade was uppercase B */
         case 'b': /* or lowercase b */
            ++bCount; /* increment bCount */
            break; /* exit switch */

         case 'C': /* grade was uppercase C */
         case 'c': /* or lowercase c */
            ++cCount; /* increment cCount */
            break; /* exit switch */

         case 'D': /* grade was uppercase D */
         case 'd': /* or lowercase d */
            ++dCount; /* increment dCount */
            break; /* exit switch */

         case 'F': /* grade was uppercase F */
         case 'f': /* or lowercase f */
            ++fCount; /* increment fCount */
            break; /* exit switch */

         case '\n': /* ignore newlines, */
         case '\t': /* tabs, */
         case ' ':  /* and spaces in input */
            break; /* exit switch */

         default: /* catch all other characters */
            printf( "Incorrect letter grade entered." ); 
            printf( " Enter a new grade.\n" ); 
            break; /* optional; will exit switch anyway */
      } /* end switch */
   
   } /* end while */

   /* output summary of results */
   printf( "\nTotals for each letter grade are:\n" );
   printf( "A: %d\n", aCount ); /* display number of A grades */
   printf( "B: %d\n", bCount ); /* display number of B grades */
   printf( "C: %d\n", cCount ); /* display number of C grades */
   printf( "D: %d\n", dCount ); /* display number of D grades */
   printf( "F: %d\n", fCount ); /* display number of F grades */

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

