/*************************************************************************
 *
 *  Program Name: Assign2P1.c
 *
 *  Problem: Create a union called "integer_union" with members char c, 
 *           short s, int i and long l. Write a program (similar to 
 *           fig10_05.c from the slides) that inputs values of type 
 *           char, short, int and long and stores the values in union 
 *           variables of type union "integer_union". Each union variable 
 *           should be printed as a char, a short, an int and a long. 
 *           Don't be surprised if you do not get the results you might 
 *           expect!
 *
 ************************************************************************/

/******************************************
 * Header files for libaray fuctions used *
 ******************************************/
#include <stdio.h>
#include <stdlib.h>

/****************************
 * Global Union Definitions *
 ****************************/
union integer_union
{
    char  c;
    short s;
    int   i;
    long  l;
};

/***********************
 * Function prototypes *
 ***********************/
void displayUnion( union integer_union uIntUnion );

/****************
 * Main program *
 ****************/
int main(void)
{
    union integer_union uIntUnion; // Holds value entered by the user

    // Query user for a char value
    printf( "Please enter a char: " );
    // and store it in the char variable of the union
    scanf( "%c", &uIntUnion.c );
    // Display what each value of the union looks like
    displayUnion( uIntUnion );

    // Query user for a short value
    printf( "Please enter a short: " );
    // and store it in the short variable of the union
    scanf( "%hd", &uIntUnion.s );
    // Display what each value of the union looks like
    displayUnion( uIntUnion );

    // Query user for an integer value
    printf( "Please enter an int: " );
    // and store it in the integer variable of the union
    scanf( "%d", &uIntUnion.i );
    // Display what each value of the union looks like
    displayUnion( uIntUnion );

    // Query user for a long value
    printf( "Please enter a long: " );
    // and store it in the long variable of the union
    scanf( "%ld", &uIntUnion.l );
    // Display what each value of the union looks like
    displayUnion( uIntUnion );

	system("pause");  // Pause until user ready for window to dissappear

    return 0;
}

/*******************
 * Function Bodies *
 *******************/

/*************************************************************************
 *
 * Function Name: displayUnion
 * Purpose:       Display values of a union variable.
 *
 * Input:        
 *
 *   union integer_union  An union of various integer values
 *
 * Output:
 *
 *   void 
 *
 * Description:       This function will display the value of an 
 *                    integer union as interpreted by the various
 *                    types the union is defined as.
 *
 ************************************************************************/
void displayUnion( union integer_union uIntUnion )
{
    printf( "char  c = %c\n", uIntUnion.c );
    printf( "short s = %hd\n", uIntUnion.s );
    printf( "int   i = %d\n", uIntUnion.i );
    printf( "long  l = %ld\n\n", uIntUnion.l );
}

