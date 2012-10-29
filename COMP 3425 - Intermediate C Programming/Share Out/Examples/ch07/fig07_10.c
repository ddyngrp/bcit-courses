/* Fig. 7.10: fig07_10.c
   Converting lowercase letters to uppercase letters
   using a non-constant pointer to non-constant data */

#include <stdio.h>
#include <ctype.h>

void convertToUppercase( char *sPtr ); /* prototype */

int main( void )
{
   char string[] = "characters and $32.98"; /* initialize char array */

   printf( "The string before conversion is: %s", string );
   convertToUppercase( string );
   printf( "\nThe string after conversion is: %s\n", string ); 
          
   return 0; /* indicates successful termination */

} /* end main */

/* convert string to uppercase letters */
void convertToUppercase( char *sPtr )
{
   while ( *sPtr != '\0' ) { /* current character is not '\0' */ 

      if ( islower( *sPtr ) ) {    /* if character is lowercase, */
         *sPtr = toupper( *sPtr ); /* convert to uppercase */
      } /* end if */

      ++sPtr;  /* move sPtr to the next character */
   } /* end while */

} /* end function convertToUppercase */



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
