/*

Program Name: Optional_1_P2.c

Author: Bob Langelaan

Problem Description:

Write a program that inputs a line of text, tokenizes the line 
with the function "strtok" and outputs the tokens in reverse 
order. For example the input: "The quick brown fox jumps over 
the dog" would be output as: "dog the over jumps fox brown quick The".

*/

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 81
#define MAX_TOKENS 20

int main( void )
{
// Declarations

   char sInputString[BUFFER_SIZE];     // Used to store the input string
   char cSeparators[] = " .,\t\n";     // This sets up blank, comma, tab, period and newline as separators
   
   char *pToken,		           // Used to store pointer to the next token found
        *pTokenArray[MAX_TOKENS];  // Used to pointers to all of the tokens found
   
   long  lCounter;    // Used to index to TokenArray element to be used next
   
// Get user to input the string to be tokenized

   printf("%s\n\n","Input the string you want tokenized: ");
   gets(sInputString);

// Establish string and get the first token: 

   pToken = strtok( sInputString, cSeparators ); // invoked with string as first parameter

// Now find remaining tokens in the string

   lCounter = -1;  // next element to be used in tokenArray -1 
   while( pToken != NULL )
   {
	  pTokenArray[++lCounter] = pToken;  // save token pointer in token pointer array
      pToken = strtok( NULL, cSeparators );  // notice that after the first time that strtok 
	                                         // is invoked, it is invoked with NULL as first parameter
   }

// Now traverse backwards through the token pointer array, displaying each one
   
   printf("\n%s\n\n","The tokens in reverse order are:");
   for (;lCounter >= 0; lCounter--)
   {
	   printf("%s\n",pTokenArray[lCounter]);
   }

   printf("\n");

// time to go home

   return 0;

}

