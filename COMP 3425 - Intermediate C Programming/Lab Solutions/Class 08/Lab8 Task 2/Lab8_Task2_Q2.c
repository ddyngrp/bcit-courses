/* Fig. 14.3: fig14_03.c
   Using command-line arguments 
   
   Modified by Bob Langelaan      */

#include <stdio.h>

int main( int argc, char *argv[] )
{ 
   int i;  // will be used as a counter;

   /* check number of command-line arguments */
   if ( argc != 4 ) {
      printf( "Usage: Lab8_Q3 string1 string2 string3\n" );
   } /* end if */

   else 
   {
	   for ( i = 1; i < 4; ++i){
		   printf ("String #%d is: %s\n",i,argv[i]);
	   } // end for loop

   } /* end else */

   return 0; /* indicates successful termination */

} /* end main */
   
   

 

/**************************************************************************
 * (C) Copyright 1992-2004 by Deitel & Associates, Inc. and               *
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
