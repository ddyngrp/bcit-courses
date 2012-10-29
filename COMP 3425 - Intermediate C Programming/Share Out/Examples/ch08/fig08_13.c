/* Fig. 8.13: fig08_13.c
   Using gets and putchar */
#include <stdio.h>

void reverse( const char * const sPtr ); /* prototype */
   
int main( void )
{  
   char sentence[ 80 ]; /* create char array */

   printf( "Enter a line of text:\n" );

   /* use gets to read line of text */
   gets( sentence ); 

   printf( "\nThe line printed backward is:\n" );
   reverse( sentence );

   return 0; /* indicates successful termination */

} /* end main */

/* recursively outputs characters in string in reverse order */
void reverse( const char * const sPtr )
{  
   /* if end of the string */
   if ( sPtr[ 0 ] == '\0' ) { /* base case */
      return; 
   } /* end if */ 
   else { /* if not end of the string */ 
      reverse( &sPtr[ 1 ] ); /* recursion step */

      putchar( sPtr[ 0 ] ); /* use putchar to display character */
   } /* end else */

} /* end function reverse */



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
