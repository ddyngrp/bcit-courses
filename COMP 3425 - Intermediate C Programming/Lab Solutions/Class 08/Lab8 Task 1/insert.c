#include <stdio.h>
#include <stdlib.h>

#include "struct_def.h"
#include "func_prototypes.h"

/* Insert a new value into the list in sorted order */

void insert( ListNodePtr *sPtr, char value )
{ 
   ListNodePtr newPtr;      /* pointer to new node */
   ListNodePtr previousPtr; /* pointer to previous node in list */
   ListNodePtr currentPtr;  /* pointer to current node in list */

   newPtr = malloc( sizeof( ListNode ) ); /* create node */

   if ( newPtr != NULL ) { /* is space available */
      newPtr->data = value; /* place value in node */
      newPtr->nextPtr = NULL; /* node does not link to another node */

      previousPtr = NULL;
      currentPtr = *sPtr;

      /* loop to find the correct location in the list */
      while ( currentPtr != NULL && value > currentPtr->data ) { 
         previousPtr = currentPtr;          /* walk to ...   */
         currentPtr = currentPtr->nextPtr;  /* ... next node */
      } /* end while */

      /* insert new node at beginning of list */
      if ( previousPtr == NULL ) { 
         newPtr->nextPtr = *sPtr;
         *sPtr = newPtr;
      } /* end if */
      else { /* insert new node between previousPtr and currentPtr */
         previousPtr->nextPtr = newPtr;
         newPtr->nextPtr = currentPtr;
      } /* end else */
   
   } /* end if */
   else {
      printf( "%c not inserted. No memory available.\n", value );
   } /* end else */

} /* end function insert */