/*
 * Assignment 4: Assign04.c
 * A program that creates two ordered linked lists
 * and merges them together into a single ordered linked list.
 *
 * Author: Steffen L. Norgren
 * Date: March 18, 2008
 */

#include <stdio.h>
#include <stdlib.h>

/* TYPEDEFINED STRUCTURE */
typedef struct listNode {
	unsigned int iData;
	struct listNode *pNextPointer;
} ListNodeType, *pListNodeTypePointer;

/* FUNCTION PROTOTYPES */
pListNodeTypePointer Create();
void PrintList(pListNodeTypePointer pCurrentPointer);
pListNodeTypePointer Merge(pListNodeTypePointer pListOnePointer,
						   pListNodeTypePointer pListTwoPointer);
void waitOnInput();

int main (void) {
	pListNodeTypePointer pListOnePointer;	/* pointer to first list */
	pListNodeTypePointer pListTwoPointer;	/* pointer to second list */
	
	printf("Input positive integers for the first list (end with a negative integer):\n\n");
	pListOnePointer = Create();
	
	printf("\nInput positive integers for the second list (end with a negative integer):\n\n");
	pListTwoPointer = Create();
	
	printf("\n\nThe first list is about to be output.\n");
	PrintList(pListOnePointer);
	
	printf("\n\nThe second list is about to be output.\n");
	PrintList(pListTwoPointer);
	
	printf("\n\nThe merged list is about to be output.\n");
	PrintList(Merge(pListOnePointer, pListTwoPointer));
	
	waitOnInput();
	
    return 0;
}

pListNodeTypePointer Create() {
	pListNodeTypePointer startPtr = NULL;		/* pointer to beginning of list */
	pListNodeTypePointer newPtr;				/* pointer to new node */
	pListNodeTypePointer previousPtr;			/* pointer to previous node */
	pListNodeTypePointer currentPtr = NULL;		/* pointer to current node */
	int value = 0;								/* value to enter into the list */
	
	while(value >= 0) {
		printf("? ");
		scanf("\n%d", &value);
		
		newPtr = malloc(sizeof(ListNodeType)); /* create node */
		
		if(newPtr != NULL) { /* is space free */
			if(value >= 0) {
				newPtr->iData = value;			/* place value in node */
				newPtr->pNextPointer = NULL;	/* node does not link to another, yet */
				
				previousPtr = NULL;
				currentPtr = startPtr;		/* set the current pointer */
				
				/* loop to find the correct location in the list */
				while(currentPtr != NULL && value > currentPtr->iData) {
					previousPtr = currentPtr;				/* walk to the ... */
					currentPtr = currentPtr->pNextPointer;	/* ... next node */
				}
				
				/* insert new node at beginning of list */
				if(previousPtr == NULL) {
					newPtr->pNextPointer = startPtr;
					startPtr = newPtr;
				}
				else { /* insert new node between previousPtr and currentPtr */
					previousPtr->pNextPointer = newPtr;
					newPtr->pNextPointer = currentPtr;
				}
			}
		}
		else {
			printf("ERROR: %c not inserted. No memory available.\n", value);
			
		}
	}
	
	return startPtr;
}

pListNodeTypePointer Merge(pListNodeTypePointer pListOnePointer,
						   pListNodeTypePointer pListTwoPointer) {
	pListNodeTypePointer pListOneCurrentPtr;
	pListNodeTypePointer pListOnePreviousPtr;
	pListNodeTypePointer pListTwoCurrentPtr;
	pListNodeTypePointer pListTwoPreviousPtr;
	pListNodeTypePointer tempPtr;
	
	pListTwoPreviousPtr = NULL;
	pListTwoCurrentPtr = pListTwoPointer;
	
	/* take apart second list and insert nodes into first list */
	while(pListTwoCurrentPtr != NULL) {
		tempPtr = pListTwoCurrentPtr;
		pListTwoPreviousPtr = pListTwoCurrentPtr;				/* walk to the ... */
		pListTwoCurrentPtr = pListTwoCurrentPtr->pNextPointer;	/* ... next node */
		
		pListOnePreviousPtr = NULL;
		pListOneCurrentPtr = pListOnePointer;
		
		/* loop to find the correct location in the first list */
		while(pListOneCurrentPtr != NULL
			  && tempPtr->iData > pListOneCurrentPtr->iData) {
			pListOnePreviousPtr = pListOneCurrentPtr;			   /* walk to the ... */
			pListOneCurrentPtr = pListOneCurrentPtr->pNextPointer; /* ... next node */
		}
		
		/* insert second list node at beginning of first list */
		if(pListOnePreviousPtr == NULL) {
			tempPtr->pNextPointer = pListOnePointer;
			pListOnePointer = tempPtr;
		}
		else { /* insert second list node between pListOnePreviousPtr and pListOneCurrentPtr */
			pListOnePreviousPtr->pNextPointer = tempPtr;
			tempPtr->pNextPointer = pListOneCurrentPtr;
		}
	}
	
	return pListOnePointer;
}

void PrintList(pListNodeTypePointer pCurrentPointer) {
	/* if list is empty */
	if (pCurrentPointer == NULL) {
		printf("The list is empty.\n");
	}
	else { 
		/* while not the end of the list */
		printf("The list is:\n\n");
		while (pCurrentPointer != NULL) { 
			printf("%d --> ", pCurrentPointer->iData);
			pCurrentPointer = pCurrentPointer->pNextPointer;   
		}
		
		printf("NULL\n");
	}
}

/* Platform independent PAUSE function */
void waitOnInput() {
	if (getchar()) {
		printf("\nPress any key to continue . . .");
		printf("%c", getchar());
	}
}