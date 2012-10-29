/* self-referential structure */
#pragma once  //use instead of #ifndef ... commented out below
//#ifndef listnode  // not necessary because of #pragma once
//#define listnode  // not necessary because of #pragma once

struct listNode {            
   char data; /* each listNode contains a character */
   struct listNode *nextPtr; /* pointer to next node*/ 
}; /* end structure listNode */

//#endif    // not necessary because of #pragma once