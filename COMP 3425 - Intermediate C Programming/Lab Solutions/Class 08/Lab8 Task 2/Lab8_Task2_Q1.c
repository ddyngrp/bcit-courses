/* Fig. 14.2: fig14_02.c
   Using variable-length argument lists 
   
   Modified by Bob Langelaan       */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int product( int i, ... ); /* prototype */

int main()
{ 
   int w = 3; 
   int x = 4; 
   int y = 5;  
   int z = 6; 

   printf( "%s%d\n%s%d\n%s%d\n%s%d\n\n",
      "w = ", w, "x = ", x, "y = ", y, "z = ", z );
   printf( "%s%d\n%s%d\n%s%d\n",
      "The product of w and x is ", product( 2, w, x ),
      "The product of w, x, and y is ", product( 3, w, x, y ),
      "The product of w, x, y, and z is ", 
      product( 4, w, x, y, z ) );

   system("pause");
   return 0; /* indicates successful termination */

} /* end main */

/* calculate average */
int product( int i, ... )
{ 
   int product_val = 1; /* initialize product_val */
   int j; /* counter for selecting arguments  */
   va_list ap; /* stores information needed by va_start and va_end */

   va_start( ap, i ); /* initializes the va_list object */

   /* process variable length argument list */
   for ( j = 1; j <= i; j++ ) {
      product_val *= va_arg( ap, int );
   } /* end for */

   va_end( ap ); /* clean up variable-length argument list */

   return product_val; /* calculate average */
} /* end function average */

 

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
