/* Fig. 10.5: fig10_05.c
   An example of a union */
#include <stdio.h>

/* number union definition */
union number {               
   int x;                    
   double y;                 
}; /* end union number */    

int main( void )
{ 
   union number value; /* define union variable */
   
   value.x = 100; /* put an integer into the union */
   printf( "%s\n%s\n%s\n  %d\n\n%s\n  %f\n\n\n",
      "Put a value in the integer member", 
      "and print both members.",
      "int:", value.x, 
      "double:", value.y );
   
   value.y = 100.0; /* put a double into the same union */
   printf( "%s\n%s\n%s\n  %d\n\n%s\n  %f\n",
      "Put a value in the floating member",
      "and print both members.",
      "int:", value.x, 
      "double:", value.y );

   return 0; /* indicates successful termination */

} /* end main */


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
