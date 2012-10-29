/*******************************************************************
*
*  COMP 3425 Assignment 3
*
*  Description:
*
*  This program ask the user for an string to be tokenized. The 
*  strtok() function is used to tokenize the string. The tokens are 
*  stored in a stack and are pushed on the stack one by one at the 
*  time they are returned from the strtok() function. Once the string
*  is fully tokenized the tokens are printed in reversed order by 
*  popping them off the stack one by one.
*
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* CONSTANTS */
#define INPUT_BUFFER	80
#define SEPARATORS		" ,\t"

/* TYPE DEFINED STRUCTURE */
typedef struct stackNode {
	char				*sToken;
	struct	stackNode	*pNextPointer;
} StackNodeType, *pStackNodeTypePointer;

/* FUNCTION PROTOYPES */
void getUserString(char *sInputString);
void push(pStackNodeTypePointer *pHeaderPointer, char *sTokenTemp);
char *pop(pStackNodeTypePointer *pHeaderPointer);
int  isEmpty(pStackNodeTypePointer pHeaderPointer);

/* MAIN */
int main(void) {
	
	/* Declarations and assignments */
	pStackNodeTypePointer	pStackNodeHeaderPointer = NULL; // Creates a header pointer for the stack
	char					sInputString[INPUT_BUFFER];		// Input string
	char					*sTokenTemp;					// For temporary storage of token

	/* Call function to get user input string */
	getUserString(sInputString);

	/* Get the first token from the input string */
	sTokenTemp = strtok(sInputString, SEPARATORS);

	/* Loop while there are tokens in the string, call the push() to put the string in the stack. 
	   Use the address of header pointer as argument for the push() function. */
	while(sTokenTemp != NULL) {
		push(&pStackNodeHeaderPointer, sTokenTemp);
		sTokenTemp = strtok(NULL, SEPARATORS);
	}
	
	/* print the content of the stack by popping the values one by one. The order in which
	   they are printed is reversed from how they where put in. LIFO (Last In First Out)*/
	printf("\nThe tokens in reverse order are:\n\n");
	while(pStackNodeHeaderPointer != NULL) {
		printf("%s\n", pop(&pStackNodeHeaderPointer));
	}

	printf("\n");

	return(0);

} /* End main */



/****************************************************************************
 *
 * Name:
 * 		getUserString
 *
 * Prototype:	
 *		char *getUserString(char *sInputString);
 *
 * Arguments:
 *		char *sInputString - A pointer to the character string to hold the
 *		user input.
 * 
 * Returns:
 *		void (Nothing)
 *
 * Description:
 *		This function ask the user for a string to be tokenized and 
 *		validates the input for proper char * variable.
 *      
 * 
 ***************************************************************************/
void getUserString(char *sInputString) {

	printf("Input the string you want tokenized:\n\n");
	while(gets(sInputString) == NULL) {  // validate input, NULL is returned if an error occurs
		printf("An error occured reading the input, try again!.\n");
		printf("Please enter a string to be tokenized:\n");
	}
}


/****************************************************************************
 *
 * Name:
 * 		push
 *
 * Prototype:	
 *		void push(pStackNodeTypePointer *pHeaderPointer, char *sTokenTemp);
 *
 * Arguments:
 *		pStackNodeTypePointer *pHeaderPointer - A pointer to the stack
 *	    header pointer.
 *		char *sTokenTemp - One token to be pushed on the stack.
 * 
 * Returns:
 *		void (Nothing)
 *
 * Description:
 *		This function push a char * variable onto the stack, and change the 
 *		stack header pointer to the new value. Memory is allocated to hold
 *		the new node.
 *      
 * 
 ***************************************************************************/
void push(pStackNodeTypePointer *pHeaderPointer, char *sTokenTemp) {

	/* Declarations */
	pStackNodeTypePointer pNewStackNodePointer; 
	
	/* Allocate memory for the new pointer */
	pNewStackNodePointer = malloc(sizeof(StackNodeType));

	
	if(pNewStackNodePointer != NULL) { /* If memory was successfully allocated */

		/* Assign token value to node variable */
		pNewStackNodePointer->sToken		= sTokenTemp;		
		/* Set nextpointer to point to the header node */
		pNewStackNodePointer->pNextPointer	= *pHeaderPointer;  
		/* Make the header pointer point to the new node */
		*pHeaderPointer	= pNewStackNodePointer;
	} 
	else { /* If memory couldn't be allocated */
		printf("%s not inserted. No memory available.\n", sTokenTemp);
	}
} /* End push() */



/****************************************************************************
 *
 * Name:
 * 		pop
 *
 * Prototype:	
 *		char *pop(pStackNodeTypePointer *pHeaderPointer);
 *
 * Arguments:
 *		pStackNodeTypePointer *pHeaderPointer - A pointer to the stack
 *	    header pointer.
 * 
 * Returns:
 *		char *sPoppedString; The string variable from the stack node varible
 *      sToken.
 *
 * Description:
 *		This function pops one node off the stack and returns the string
 *      sPoppedToken contained in the node. A temporary pointer is used 
 *		to change the header pointer to point to the next node in the stack.
 *      
 * 
 ***************************************************************************/
char *pop(pStackNodeTypePointer *pHeaderPointer) {
	
	/* Declarations */
	pStackNodeTypePointer	pTempNodePointer; /* Create temporary node */
	char					*sPoppedToken; 
	
	/* Make temp pointer point to stack header node */
	pTempNodePointer	= *pHeaderPointer;
	/* Get the token variable from the header node */
	sPoppedToken		= (*pHeaderPointer)->sToken;
	/* Make header pointer point to the next node in the stack */
	*pHeaderPointer		= (*pHeaderPointer)->pNextPointer;
	
	/* Discard of the temporary pointer, i.e. the node that was popped off the stack */
	free(pTempNodePointer);

	/* Return token string */
	return(sPoppedToken);
}



/****************************************************************************
 *
 * Name:
 * 		isEmpty
 *
 * Prototype:	
 *		int isEmpty(pStackNodeTypePointer pHeaderPointer)
 *
 * Arguments:
 *		pStackNodeTypePointer pHeaderPointer - Header pointer of stack.
 * 
 * Returns:
 *		int - If header pointer is NULL return TRUE (!0) otherwice FALSE 0.
 *
 * Description:
 *		This function checks the header pointer of the stack to see if there
 *      are any nodes in the stack. If the stack is empty pointer is NULL
 *		and TRUE (!0) is returned.
 * 
 ***************************************************************************/
int isEmpty(pStackNodeTypePointer pHeaderPointer) {
	
	/* If header pointer is NULL return TRUE (!0) */
	return(pHeaderPointer == NULL);
}