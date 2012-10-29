/*
 * Assignment 3: Assign03.c
 * Author: Steffen L. Norgren
 * Date: March 3, 2008
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 81

struct stackNode {
	char *sToken;
	struct stackNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

/* prototypes */
void push( StackNodePtr *topPtr, char *sToken );
char * pop( StackNodePtr *topPtr );
int isEmpty( StackNodePtr topPtr );

int main( void )
{
	StackNodePtr stackPtr = NULL;
	char sInputString[BUFFER_SIZE];
	char cSeparators[] = " .,\t\n";
	char *pToken;
	
	printf("%s\n\n","Input the string you want tokenized: ");
	fgets(sInputString, BUFFER_SIZE, stdin);
	
	pToken = strtok(sInputString, cSeparators);
	
	while(pToken != NULL) {
		push(&stackPtr, pToken);
		pToken = strtok(NULL, cSeparators);
	}

	printf("\nThe tokens in reverse order are:\n\n");
	while(!isEmpty(stackPtr)) {
		printf("%s\n", pop(&stackPtr));
	}
	
	return 0;
}

void push(StackNodePtr *topPtr, char *sToken) {
	StackNodePtr newPtr; /* pointer to new node */
	
	newPtr = malloc(sizeof(StackNode));
	
	if (newPtr != NULL) {
		newPtr->sToken = sToken;
		newPtr->nextPtr = *topPtr;
		*topPtr = newPtr;
	}
	else {
		printf("%d not inserted. No memory available.\n", sToken);
	}
}

char * pop(StackNodePtr *topPtr)
{ 
	StackNodePtr tempPtr;
	char *popValue;
	
	tempPtr = *topPtr;
	popValue = (*topPtr)->sToken;
	*topPtr = (*topPtr)->nextPtr;
	free(tempPtr);
	
	return popValue;
}

int isEmpty(StackNodePtr topPtr)
{ 
	return topPtr == NULL;
}