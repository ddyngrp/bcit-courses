/*
 * Assignment 2 Part 2: Assign2P2.c
 * Author: Steffen L. Norgren - A00683006
 * Date: February 19, 2007
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Function prototype */
unsigned reverseBits(unsigned value);
void displayBits(unsigned value);
void waitOnInput();

int main (void) {
	unsigned ui;
	
	printf("\n%s%u%s","Please enter an unsigned integer "
		   "(whole number between 0 and ", ULONG_MAX, "):\n\n");

	scanf("%u", &ui);
	
	displayBits(ui);

	printf("\n\n%s%u%s", "The result of reversing ", ui, " is:\n");
	displayBits(reverseBits(ui));

	waitOnInput();
    return 0;
}

/* Reverse Bits */
unsigned reverseBits(unsigned value) {
	unsigned returnUnsigned = 0;
	int c; /* counter */

	for(returnUnsigned = c = 0; c < 32; c++) {
		/* left shift the return value by 1 and the value anded by 1 */
		returnUnsigned = (returnUnsigned << 1) + (value & 1);
		/* right shift the value by 1 */
		value >>= 1;
	}
	
	return returnUnsigned;
}

/* display bits of an unsigned integer value */
void displayBits(unsigned value)
{ 
   unsigned c; /* counter */

   /* declare displayMask and left shift 31 bits */
   unsigned displayMask = 1 << 31;

   printf( "\n%u = ", value );

   /* loop through bits */
   for ( c = 1; c <= 32; c++ ) { 
      putchar( value & displayMask ? '1' : '0' );
      value <<= 1; /* shift value left by 1 */

      if ( c % 8 == 0 ) { /* output a space after 8 bits */
         putchar( ' ' );
      } /* end if */

   } /* end for */

   putchar( '\n' );
}

/* Platform independent PAUSE function */
void waitOnInput() {
	if (getchar()) {
		printf("\nPress any key to continue . . .");
		printf("%c", getchar());
	}
}