/* Fig. 7.17: fig07_17.c
   Demonstrating the sizeof operator */
#include <stdio.h>

int main( void )
{ 
   char c;           
   short s;         
   int i;       
   long l;         
   float f;        
   double d;         
   long double ld;   
   int array[ 20 ];  /* create array of 20 int elements */
   int *ptr = array; /* create pointer to array */

   printf( "     sizeof c = %d\tsizeof(char)  = %d"   
           "\n     sizeof s = %d\tsizeof(short) = %d"   
           "\n     sizeof i = %d\tsizeof(int) = %d"   
           "\n     sizeof l = %d\tsizeof(long) = %d"   
           "\n     sizeof f = %d\tsizeof(float) = %d"   
           "\n     sizeof d = %d\tsizeof(double) = %d"   
           "\n    sizeof ld = %d\tsizeof(long double) = %d"   
           "\n sizeof array = %d"   
           "\n   sizeof ptr = %d\n",    
          sizeof c, sizeof( char ), sizeof s, sizeof( short ), sizeof i,
          sizeof( int ), sizeof l, sizeof( long ), sizeof f, 
          sizeof( float ), sizeof d, sizeof( double ), sizeof ld, 
          sizeof( long double ), sizeof array, sizeof ptr );  

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

