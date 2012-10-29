
#include <stdio.h>
#include <stdlib.h>

#include "struct_def.h"
#include "func_prototypes.h"

/* Delete a list element */
char delete( ListNodePtr *sPtr, char value )
{ 
   ListNodePtr previousPtr; /* pointer to previous node in list */
   ListNodePtr currentPtr;  /* pointer to current node in list */
   ListNodePtr tempPtr;     /* temporary node pointer */

   /* delete first node */
   if ( value == ( *sPtr )->data ) { 
      tempPtr = *sPtr; /* hold onto node being removed */
      *sPtr = ( *sPtr )->nextPtr; /* de-thread the node */
      free( tempPtr ); /* free the de-threaded node */
      return value;
   } /* end if */
   else { 
      previousPtr = *sPtr;
      currentPtr = ( *sPtr )->nextPtr;

      /* loop to find the correct location in the list */
      while ( currentPtr != NULL && currentPtr->data != value ) { 
         previousPtr = currentPtr;         /* walk to ...   */
         currentPtr = currentPtr->nextPtr; /* ... next node */  
      } /* end while */

      /* delete node at currentPtr */
      if ( currentPtr != NULL ) { 
         tempPtr = currentPtr;
         previousPtr->nextPtr = currentPtr->nextPtr;
         free( tempPtr );
         return value;
      } /* end if */
     
   } /* end else */

   return '\0';

} /* end function delete */