/**************************************************************************

  COMP 3425 Assignment 02 Part 2

***************************************************************************

Assign2P2.c

This program uses a function to reverse the order of the bits in an
unsigned integer value, which is input by the user. The unsigned integer
is printed before and after the reverse function is called to confirm
that the bits are reversed properly.

**************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define INT_BITS 32

void DisplayBits(unsigned int iOriginalInt);
unsigned int ReverseBits(unsigned int iOriginalInt);

int main(void)
{
	// variable declaration
	unsigned int	iOriginalInt,			// user entered unsigned int
					iReversedInt;			// for ReverseBits function

	// assign values
	iOriginalInt = iReversedInt = 0;

	// get an unsigned integer from the user
	printf("%s%s%u%s", "Please enter an unsigned integer ",
		"(whole number between 0 and ", UINT_MAX, "):\n\n");
	scanf("%u", &iOriginalInt);

	// display the original integer in bits
	DisplayBits(iOriginalInt);

	// reverse the bits of the original integer
	iReversedInt = ReverseBits(iOriginalInt);

	// display the resulting reversed integer
	printf("\n\nThe result of reversing %u is:\n\t", iOriginalInt);
	DisplayBits(iReversedInt);

	// easier readibility
	printf("\n");

	// wait for user to signal end of program
	system("pause");

	return (0);
}


/**************************************************************************
 *
 * Name:
 * 		DisplayBits - display the bits in an unsigned integer
 *
 * Synopsis:	
 *		void DisplayBits(unsigned int iOriginalInt)
 *
 * Arguments:
 *		unsigned int iOriginalInt - the unsigned integer entered by user
 * 
 * Returns:
 *		None.
 *
 * Description:
 *		This function prints the bits of an unsigned integer passed to it.
 *
 * Assumptions:
 * 		Not applicable.
 * 
**************************************************************************/
void DisplayBits(unsigned int iOriginalInt)
{
	unsigned int iCounter = 0;				// loop counter
	unsigned int iDisplayMask = 1 << (INT_BITS-1);	// define, left shift 31 bits

	printf("\n");							// easier readibility

	printf("%u = ", iOriginalInt);			// print the integer

	// loop through and display bits of the integer
	// NOTE: original code from class slides
	for (iCounter = 1; iCounter <= INT_BITS; iCounter++)
	{
		putchar(iOriginalInt & iDisplayMask ? '1' : '0');
		iOriginalInt <<=1;					// shift value left by 1

		if (iCounter % 8 == 0)				// space after 8 bits
		{
			putchar(' ');
		}
	}

	putchar('\n');							// easier readability
} /* end DisplayBits function */


/**************************************************************************
 *
 * Name:
 * 		ReverseBits - reverse the bits of an unsigned integer
 *
 * Synopsis:	
 *		unsigned int ReverseBits(unsigned int iOriginalInt)
 *
 * Arguments:
 *		unsigned int iOriginalInt - the unsigned int entered by user
 * 
 * Returns:
 *		unsigned int iReverseResult - the result of the reverse function
 *
 * Description:
 *		This function reverses the bits of an unsigned int passed to it,
 *		assigning the bits to another unsigned int (iReversedResult) and
 *		then passes the new unsigned int back.
 *
 * Assumptions:
 * 		Not applicable.
 * 
**************************************************************************/
unsigned int ReverseBits(unsigned int iOriginalInt)
{
	unsigned int iReversedResult = 0;		// to hold reversed bits
	unsigned int iDisplayMask = 1;			// for shifting bits
	int iCounter = 0;						// for loop counter

	// loop through the original integer;
	for (iCounter = 0; iCounter <= (INT_BITS-1); iCounter++)
	{	
		// iReversedResult is shifted left one bit, and then the first
		// bit is filled with 0
		iReversedResult <<= 1;

		// bitwise AND compare between the original integer and the
		// iDisplayMask (being 1). If both of them are one, the right
		// side of the equation is one. Then iReversedResult is compared
		// using bitwise inclusive; result is set to iReversedResult. 
		iReversedResult |= (iOriginalInt & iDisplayMask);

		// referenced bit in the iOriginalInt is shifted right one bit
		iOriginalInt >>= 1;

		// the above process continues until all bits of the original
		// integer have been read and placed in the reversed integer
	}

	return iReversedResult;				// return the reversed integer
} /* end ReverseBits function */
