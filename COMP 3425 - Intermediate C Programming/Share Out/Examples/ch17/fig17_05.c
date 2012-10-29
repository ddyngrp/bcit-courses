// Fig 17.5: fig17_05.c
// Declaring a loop counter before a for statement in C89
#include <stdio.h>

int main( void )
{
   printf( "Values of x\n" );
   
   // output values 1 through 5
   int x; // declare loop counter
   for ( x = 1; x <= 5; x++ ) // initialize loop counter
      printf( "%d\n", x );
             
   printf( "Value of x is %d\n", x ); // x is still in scope    

   return 0; // indicates successful termination
} // end main


 /*************************************************************************
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
