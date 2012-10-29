// Fig 17.15: fig17_15.c
// Using variable-length arrays in C99
#include <stdio.h>

void printArray( int sz, int arr[ sz ] ); // function that accepts a VLA

int main()
{
   int arraySize; // size of array
   printf( "Enter array size in words: " );
   scanf( "%d", &arraySize );

   // using a non-constant expression for array's size
   int array[ arraySize ]; // declare variable-length array
   // test sizeof operator on VLA
   int a = sizeof( array );
   printf( "\nsizeof yields array size of %d bytes\n\n", a );
   
   // assign elements of VLA
   for ( int i = 0; i < arraySize; i++ ) {
      array[ i ] = i * i;
   } // end for       
   
   printArray( arraySize, array ); // pass VLA to function

   return 0; // indicates successful termination
} // end main

void printArray( int size, int array[ size ] )
{
   // output contents of array
   for ( int i = 0; i < size; i++ ) {
      printf( "array[%d] = %d\n", i, array[ i ] );
   } // end for   
} // end function printArray



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
