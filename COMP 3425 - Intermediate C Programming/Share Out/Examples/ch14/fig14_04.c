/* Fig. 14.4: fig14_04.c
   Using the exit and atexit functions */
#include <stdio.h>
#include <stdlib.h>

void print( void ); /* prototype */

int main( void )
{ 
   int answer; /* user's menu choice */

   atexit( print ); /* register function print */
   printf( "Enter 1 to terminate program with function exit"
      "\nEnter 2 to terminate program normally\n" );
   scanf( "%d", &answer );

   /* call exit if answer is 1 */
   if ( answer == 1 ) { 
      printf( "\nTerminating program with function exit\n" );
      exit( EXIT_SUCCESS );
   } /* end if */

   printf( "\nTerminating program by reaching the end of main\n" );

   return 0; /* indicates successful termination */

} /* end main */

/* display message before termination */
void print( void )
{ 
   printf( "Executing function print at program "
      "termination\nProgram terminated\n" );
} /* end function print */

 

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
