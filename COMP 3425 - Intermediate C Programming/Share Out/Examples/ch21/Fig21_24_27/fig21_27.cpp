// Fig. 21.27: fig21_27.cpp
// Hiding a class’s private data with a proxy class.
#include <iostream>
using std::cout;
using std::endl;

#include "Interface.h" // Interface class definition

int main()
{
   Interface i( 5 ); // create Interface object
 
   cout << "Interface contains: " << i.getValue() 
      << " before setValue" << endl;

   i.setValue( 10 );

   cout << "Interface contains: " << i.getValue() 
      << " after setValue" << endl;
   return 0;
} // end main

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
 **************************************************************************/
