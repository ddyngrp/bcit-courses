/*

Program Name: Assign1P1.c

Author: Bob Langelaan

Problem Description:

Write a program that loads 10-element array number with random 
integers from 1 to 1000.  For each value, print the value and a
running total of the number of characters printed.   Use the %n
conversion specifier to determine the number of characters output
for each value.  Print the total number of characters output for 
all values up to and including the current value each time the
current value is printed. 

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10

int main( void )
{ 
   int iRandomNumbers[ ARRAY_SIZE ]; /* random integers from 1 to 1000 */
   int iLoopCounter;         /* loop counter */
   int iCount;               /* number of characters in current value */
   int iTotalCount = 0;      /* total characters in array */

   _set_printf_count_output( 1 );  // to allow use of %n

   srand( time( NULL ) ); // seed random # generator
   
   /* fill the array with random numbers */
   for ( iLoopCounter = 0; iLoopCounter <= (ARRAY_SIZE-1); iLoopCounter++ ) {
      iRandomNumbers[ iLoopCounter ] = 1 + rand() % 1000;
   } /* end for */
    
   /* print table headers */
   printf( "%s\t%s\n", "Value", "Total characters\n" );
     
   /* loop through 10 elements */
   for ( iLoopCounter = 0; iLoopCounter <= (ARRAY_SIZE-1); iLoopCounter++ ) { 
      printf( "%d%n", iRandomNumbers[ iLoopCounter ], &iCount );
      iTotalCount+= iCount; /* update totalCount */
      printf( "\t%d\n", iTotalCount );
   } /* end for */

   printf("\n");
   
   system("pause");
   return 0; /* indicate successful termination */

} /* end main */

