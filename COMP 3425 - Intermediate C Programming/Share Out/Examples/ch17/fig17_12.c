// Fig 17.12: fig17_12.c
// Using implicit int return type in C89
#include <stdio.h>

returnImplicitInt(); // prototype with unspecified return type
int demoImplicitInt(x); // prototype missing a parameter name type

int main( void )
{
   int x;
   int y;
   
   // assign data of unspecified return type to int
   x = returnImplicitInt(); 
   
   // pass in an int to a function with an unspecified type
   y = demoImplicitInt(82);
   
   
   printf( "x is %d\n", x );
   printf( "y is %d\n", y );
   return 0; // indicates successful termination

} // end main

returnImplicitInt() 
{
   return 77; // returning an int when return type is not specified
} // end function returnImplicitInt

int demoImplicitInt(x)
{
   return x;  
} // end function demoImplicitInt



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
