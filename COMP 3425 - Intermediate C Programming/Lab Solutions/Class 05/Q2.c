/* Fig. 12.13: fig12_13.c
   Operating and maintaining a queue 
   
   Modified by Bob Langelaan   */

#include <stdio.h>
#include <stdlib.h>

/* self-referential structure */
struct queueNode {   
   char data;                 /* define data as a char */
   struct queueNode *nextPtr; /* queueNode pointer */
}; /* end structure queueNode */

typedef struct queueNode QueueNode;
typedef QueueNode *QueueNodePtr;

/* function prototypes */
void printQueue( QueueNodePtr currentPtr );
int isEmpty( QueueNodePtr headPtr );
char dequeue( QueueNodePtr *headPtr, QueueNodePtr *tailPtr );
void enqueue( QueueNodePtr *headPtr, QueueNodePtr *tailPtr, 
              char value );
void instructions( void );

void duplicateValues (QueueNodePtr headPtr, QueueNodePtr * ptailPtr);

/* function main begins program execution */
int main()
{ 
   QueueNodePtr headPtr = NULL; /* initialize headPtr */
   QueueNodePtr tailPtr = NULL; /* initialize tailPtr */
   int choice;                  /* user's menu choice */
   char item;                   /* char input by user */

   instructions(); /* display the menu */
   printf( "? " );
   scanf( "%d", &choice );

   /* while user does not enter 3 */
   while ( choice != 4 ) { 

      switch( choice ) { 

         /* enqueue value */
         case 1:
            printf( "Enter a character: " );
            scanf( "\n%c", &item );
            enqueue( &headPtr, &tailPtr, item );
            printQueue( headPtr );
            break;

         /* dequeue value */
         case 2:

            /* if queue is not empty */
            if ( !isEmpty( headPtr ) ) { 
               item = dequeue( &headPtr, &tailPtr );
               printf( "%c has been dequeued.\n", item );
            } /* end if */

            printQueue( headPtr );
            break;

			/* add duplicate values */
         case 3:
			/* if queue is not empty */
            if ( !isEmpty( headPtr ) ) { 
               duplicateValues( headPtr, &tailPtr );
            } /* end if */
            
            printQueue( headPtr );
            break;

         default:
            printf( "Invalid choice.\n\n" );
            instructions();
            break;

      } /* end switch */

      printf( "? " );
      scanf( "%d", &choice );
   } /* end while */

   printf( "End of run.\n" );
   
   system("pause");
   return 0; /* indicates successful termination */

} /* end main */

/* display program instructions to user */
void instructions( void )
{ 
   printf ( "Enter your choice:\n"
           "   1 to add an item to the queue\n"
           "   2 to remove an item from the queue\n"
		   "   3 to add a duplicate item for each item in the queue\n"
           "   4 to end\n" );
} /* end function instructions */

/* insert a node a queue tail */
void enqueue( QueueNodePtr *headPtr, QueueNodePtr *tailPtr, 
              char value )
{ 
   QueueNodePtr newPtr; /* pointer to new node */

   newPtr = malloc( sizeof( QueueNode ) );

   if ( newPtr != NULL ) { /* is space available */ 
      newPtr->data = value;
      newPtr->nextPtr = NULL;

      /* if empty, insert node at head */
      if ( isEmpty( *headPtr ) ) {
         *headPtr = newPtr;
      } /* end if */
      else {
         ( *tailPtr )->nextPtr = newPtr;
      } /* end else */

      *tailPtr = newPtr;
   } /* end if */
   else {
      printf( "%c not inserted. No memory available.\n", value );
   } /* end else */

} /* end function enqueue */

/* remove node from queue head */
char dequeue( QueueNodePtr *headPtr, QueueNodePtr *tailPtr )
{ 
   char value;           /* node value */
   QueueNodePtr tempPtr; /* temporary node pointer */

   value = ( *headPtr )->data;
   tempPtr = *headPtr;
   *headPtr = ( *headPtr )->nextPtr;

   /* if queue is empty */
   if ( *headPtr == NULL ) {
      *tailPtr = NULL;
   } /* end if */

   free( tempPtr );

   return value;

} /* end function dequeue */

/* Return 1 if the list is empty, 0 otherwise */
int isEmpty( QueueNodePtr headPtr )
{ 
   return headPtr == NULL;

} /* end function isEmpty */

/* Print the queue */
void printQueue( QueueNodePtr currentPtr )
{ 

   /* if queue is empty */
   if ( currentPtr == NULL ) {
      printf( "Queue is empty.\n\n" );
   } /* end if */
   else { 
      printf( "The queue is:\n" );

      /* while not end of queue */
      while ( currentPtr != NULL ) { 
         printf( "%c --> ", currentPtr->data );
         currentPtr = currentPtr->nextPtr;
      } /* end while */

      printf( "NULL\n\n" );
   } /* end else */

} /* end function printQueue */

/* add dupicate entries for each entry in the queue */
void duplicateValues (QueueNodePtr headPtr, QueueNodePtr * ptailPtr)
{
	QueueNodePtr previousPtr; /* pointer to previous node in list */
	QueueNodePtr currentPtr;  /* pointer to current node in list */
	QueueNodePtr tempPtr;     /* temporary node pointer */

	previousPtr = headPtr;

	/* Walk through list of nodes, duplicating each one */

	do {

		currentPtr = previousPtr->nextPtr;

		// create new node and initialize it.
		tempPtr = malloc( sizeof( QueueNode ) );
		tempPtr->data = previousPtr->data;
		tempPtr->nextPtr = NULL;

		// connect new node to queue list
		previousPtr->nextPtr = tempPtr;
		tempPtr->nextPtr = currentPtr;

		// walk to next node
		previousPtr = tempPtr->nextPtr;

	} while (previousPtr != NULL);

	// One last step - update tailPtr

	*ptailPtr = tempPtr;

} /* end function duplicateValues */
















/**************************************************************************
 * (C) Copyright 1992-2004 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
