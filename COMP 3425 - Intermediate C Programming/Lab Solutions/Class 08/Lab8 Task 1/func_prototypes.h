//typedefs

typedef struct listNode ListNode; /* synonym for struct listNode */
typedef ListNode *ListNodePtr; /* synonym for ListNode* */

//function prototypes

void insert( ListNodePtr *sPtr, char value );
char delete( ListNodePtr *sPtr, char value );
void instructions( void );
int isEmpty( ListNodePtr sPtr );
void printList( ListNodePtr currentPtr );
