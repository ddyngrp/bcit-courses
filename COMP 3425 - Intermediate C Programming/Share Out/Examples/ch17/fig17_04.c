// Fig 17.4: fig17_04.c
// Attempting to declare a variable after its use in C99
#include <stdio.h>

int main( void )
{
   int x = 1; // declare x

   printf( "The value of x is %d\n", x ); // output x
   printf( "The value of y is %d\n", y ); // output y (error)

   int y = 2; // declare y

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
