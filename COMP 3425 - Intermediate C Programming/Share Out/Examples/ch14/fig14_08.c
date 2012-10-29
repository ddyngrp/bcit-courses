/* Fig. 14.8: fig14_08.c
   Using signal handling */
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

void signalHandler( int signalValue ); /* prototype */

int main( void )
{ 
   int i; /* counter used to loop 100 times */
   int x; /* variable to hold random values between 1-50 */
 
   signal( SIGINT, signalHandler ); /* register signal handler */
   srand( clock() );
   
   /* output numbers 1 to 100 */
   for ( i = 1; i <= 100; i++ ) { 
      x = 1 + rand() % 50; /* generate random number to raise SIGINT */
      
      /* raise SIGINT when x is 25 */
      if ( x == 25 ) {
         raise( SIGINT );     
      } /* end if */

      printf( "%4d", i );
      
      /* output \n when i is a multiple of 10 */
      if ( i % 10 == 0 ) {
         printf( "\n" );
      } /* end if */

   } /* end for */

   return 0; /* indicates successful termination */

} /* end main */

/* handles signal */ 
void signalHandler( int signalValue )
{ 
   int response; /* user's response to signal (1 or 2) */
   
   printf( "%s%d%s\n%s",
      "\nInterrupt signal ( ", signalValue, " ) received.",
      "Do you wish to continue ( 1 = yes or 2 = no )? " );
   
   scanf( "%d", &response );
   
   /* check for invalid responses */
   while ( response != 1 && response != 2 ) { 
      printf( "( 1 = yes or 2 = no )? " );
      scanf( "%d", &response );
   } /* end while */
   
   /* determine if it is time to exit */
   if ( response == 1 ) {

      /* reregister signal handler for next SIGINT */
      signal( SIGINT, signalHandler );
   } /* end if */
   else {
      exit( EXIT_SUCCESS );
   } /* end else */
 
} /* end function signalHandler */



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
