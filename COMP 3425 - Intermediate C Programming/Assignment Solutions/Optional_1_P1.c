/*

Program Name: Optional_1_P1.c

Author: Bob Langelaan

Problem Description:

Write a program that uses "strncmp" to compare two strings input 
by the user. The number of characters to be compared should be 
the length of the shortest input string (assume input string will 
always be 2 or more characters). The program should state whether
the first string is less than, equal to, or greater than the 
second string.

*/

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 20

int main( void )
{

// Declarations

   char sInputString1[BUFFER_SIZE],  // used to store the first input string
        sInputString2[BUFFER_SIZE];  // used to store the second input string

   long lLength1,	     // used to store the length of the first string
	    lLength2,        // used to store the length of the second string
        lLengthCompare;  // will be the 3rd arguement to the strncmp() function

   char sComparisonResult[20]; // used to store result string 
   long lResult;  // used to store result of strncmp() function

// Have user input two strings

   printf("%s\n\n","Input the first string: ");
   gets(sInputString1);

   printf("\n%s\n\n","Input the second string: ");
   gets(sInputString2);

// Use the strlen function to find out length of the two strings

   lLength1 = (long) strlen( sInputString1 );
   lLength2 = (long) strlen( sInputString2 );

   if (lLength1 < lLength2)
   {
	   lLengthCompare = lLength1;  // the first string is the shorter than the second string
   }
   else
   {
       lLengthCompare = lLength2;  // the second string is shorter or equal in length to first string
   }

// Output results

   printf("\n%s\n\t\t%s\n\t\t%s\n\n","Compare strings:",sInputString1,sInputString2);
 
   lResult = strncmp( sInputString1 ,sInputString2 ,lLengthCompare );
   
   if( lResult > 0 )
   {
      strcpy( sComparisonResult, "greater than" );
   }
   else if( lResult < 0 )
   {
      strcpy( sComparisonResult, "less than" );
   }
   else
   {
      strcpy( sComparisonResult, "equal to" );
   }

   printf("%s%s%s","Result:\t\tString 1 is ",sComparisonResult," String 2\n\n");

// time to go home

   return 0;

}