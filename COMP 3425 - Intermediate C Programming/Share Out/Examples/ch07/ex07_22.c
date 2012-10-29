/* ex07_22.c */
/* what does this program do? */
#include <stdio.h>

int mystery2( const char *s ); /* prototype */

int main( void )
{
   char string[ 80 ]; /* create char array */

   printf( "Enter a string: ");
   scanf( "%s", string ); 

   printf( "%d\n", mystery2( string ) );

   return 0; /* indicates successful termination */

} /* end main */

/* What does this function do? */
int mystery2( const char *s ) 
{
   int x; /* counter */

   /* loop through string */
   for ( x = 0; *s != '\0'; s++ ) {
      x++;
   } /* end for */

   return x;

} /* end function mystery2 */



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