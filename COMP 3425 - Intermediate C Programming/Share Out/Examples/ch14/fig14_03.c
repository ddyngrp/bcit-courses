/* Fig. 14.3: fig14_03.c
   Using command-line arguments */
#include <stdio.h>

int main( int argc, char *argv[] )
{ 
   FILE *inFilePtr;  /* input file pointer */
   FILE *outFilePtr; /* output file pointer */
   int c;            /* define c to hold characters input by user */

   /* check number of command-line arguments */
   if ( argc != 3 ) {
      printf( "Usage: mycopy infile outfile\n" );
   } /* end if */
   else {

      /* if input file can be opened */
      if ( ( inFilePtr = fopen( argv[ 1 ], "r" ) ) != NULL ) {

         /* if output file can be opened */
         if ( ( outFilePtr = fopen( argv[ 2 ], "w" ) ) != NULL ) {

            /* read and output characters */
            while ( ( c = fgetc( inFilePtr ) ) != EOF ) {
               fputc( c, outFilePtr );
            } /* end while */

         } /* end if */ 
         else { /* output file could not be opened */
            printf( "File \"%s\" could not be opened\n", argv[ 2 ] ); 
         } /* end else */

      } /* end if */
      else { /* input file could not be opened */
         printf( "File \"%s\" could not be opened\n", argv[ 1 ] );
      } /* end else */

   } /* end else */

   return 0; /* indicates successful termination */

} /* end main */
   
   

 

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
