// Fig. 27.7: Fig27_07.cpp
// Demonstrating set_new_handler.
#include <iostream>
using std::cerr;
using std::cout;

#include <new> // standard operator new and set_new_handler
using std::set_new_handler;

#include <cstdlib> // abort function prototype
using std::abort;

// handle memory allocation failure
void customNewHandler()                  
{                                        
   cerr << "customNewHandler was called";
   abort();                              
} // end function customNewHandler       

// using set_new_handler to handle failed memory allocation
int main()
{
   double *ptr[ 50 ];

   // specify that customNewHandler should be called on 
   // memory allocation failure                         
   set_new_handler( customNewHandler );                 

   // allocate memory for ptr[ i ]; customNewHandler will be
   // called on failed memory allocation
   for ( int i = 0; i < 50; i++ )
   {
      ptr[ i ] = new double[ 50000000 ]; // may throw exception
      cout << "Allocated 50000000 doubles in ptr[ " << i << " ]\n";
   } // end for

   return 0;
}  // end main

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
