/* Fig. 10.2: fig10_02.c
   Using the structure member and 
   structure pointer operators */
#include <stdio.h>

/* card structure definition */         
struct card {                           
   char *face; /* define pointer face */
   char *suit; /* define pointer suit */
}; /* end structure card */             

int main( void )
{ 
   struct card aCard; /* define one struct card variable */   
   struct card *cardPtr; /* define a pointer to a struct card */

   /* place strings into aCard */
   aCard.face = "Ace";   
   aCard.suit = "Spades";

   cardPtr = &aCard; /* assign address of aCard to cardPtr */

   printf( "%s%s%s\n%s%s%s\n%s%s%s\n", aCard.face, " of ", aCard.suit,
      cardPtr->face, " of ", cardPtr->suit,                           
      ( *cardPtr ).face, " of ", ( *cardPtr ).suit );                 
   
   return 0; /* indicates successful termination */
 
} /* end main */




/**************************************************************************
 * (C) Copyright 1992-2007 by Deitel & Associates, Inc. and               *
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
