/* ex07_21.c */
/* What does this program do? */
#include <stdio.h>

void mystery1( char *s1, const char *s2 ); /* prototype */

int main( void )
{
   char string1[ 80 ]; /* create char array */
   char string2[ 80 ]; /* create char array */

   printf( "Enter two strings: " );
   scanf( "%s%s" , string1, string2 );

   mystery1( string1, string2 );

   printf("%s", string1 );

   return 0; /* indicates successful termination */

} /* end main */

/* What does this function do? */
void mystery1( char *s1, const char *s2 )
{
   while ( *s1 != '\0' ) {
      s1++;
   } /* end while */

   for ( ; *s1 = *s2; s1++, s2++ ) {
      ;   /* empty statement */
   } /* end for */

} /* end function mystery1 */



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
