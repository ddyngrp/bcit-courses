/* Fig. 16.1: fig16_01.c
   The selection sort algorithm. */
#define SIZE 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* function prototypes */
void selectionSort( int array[], int length );
void swap( int array[], int first, int second );
void printPass( int array[], int length, int pass, int index );

int main( void )
{
   int array[ SIZE ]; /* declare the array of ints to be sorted */
   int i; /* int used in for loop */
    
   srand( time( NULL ) ); /* seed the rand function */
   
   for ( i = 0; i < SIZE; i++ )
      array[ i ] = rand() % 90 + 10; /* give each element a value */
       
   printf( "Unsorted array:\n" );
    
   for ( i = 0; i < SIZE; i++ ) /* print the array */
      printf( "%d  ", array[ i ] );
        
   printf( "\n\n" );
   selectionSort( array, SIZE );
   printf( "Sorted array:\n" );
    
   for ( i = 0; i < SIZE; i++ ) /* print the array */
      printf( "%d  ", array[ i ] );
        
   return 0;
} /* end function main */

/* function that selection sorts the array */
void selectionSort( int array[], int length )
{
   int smallest; /* index of smallest element */
   int i, j; /* ints used in for loops */
    
   /* loop over length - 1 elements */
   for ( i = 0; i < length - 1; i++ ) {
      smallest = i; /* first index of remaining array */
        
      /* loop to find index of smallest element */
      for ( j = i + 1; j < length; j++ )
         if ( array[ j ] < array[ smallest ] )
            smallest = j;
                
      swap( array, i, smallest ); /* swap smallest element */
      printPass( array, length, i + 1, smallest ); /* output pass */
   } /* end for */
} /* end function selectionSort */

/* function that swaps two elements in the array */
void swap( int array[], int first, int second )
{
   int temp; /* temporary integer */
   temp = array[ first ];
   array[ first ] = array[ second ];
   array[ second ] = temp;
} /* end function swap */

/* function that prints a pass of the algorithm */
void printPass( int array[], int length, int pass, int index )
{
   int i; /* int used in for loop */
    
   printf( "After pass %2d: ", pass );
    
   /* output elements till selected item */
   for ( i = 0; i < index; i++ )
      printf( "%d  ", array[ i ] );
        
   printf( "%d* ", array[ index ] ); /* indicate swap */
    
   /* finish outputting array */
   for ( i = index + 1; i < length; i++ )
      printf( "%d  ", array[ i ] );
        
   printf( "\n               " ); /* for alignment */
   
   /* indicate amount of array that is sorted */
   for ( i = 0; i < pass; i++ )
      printf( "--  " );
    
   printf( "\n" ); /* add newline */
} /* end function printPass */
