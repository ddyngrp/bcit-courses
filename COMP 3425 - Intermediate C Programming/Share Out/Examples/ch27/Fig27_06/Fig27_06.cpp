// Fig. 27.6: Fig27_06.cpp
// Demonstrating standard new throwing bad_alloc when memory
// cannot be allocated.
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

#include <new> // standard operator new
using std::bad_alloc;                  

int main()
{
   double *ptr[ 50 ];
   
   // allocate memory for ptr
   try 
   {
      // allocate memory for ptr[ i ]; new throws bad_alloc on failure
      for ( int i = 0; i < 50; i++ ) 
      {
         ptr[ i ] = new double[ 50000000 ]; // may throw exception
         cout << "Allocated 50000000 doubles in ptr[ " << i << " ]\n";
      } // end for
   } // end try

   // handle bad_alloc exception
   catch ( bad_alloc &memoryAllocationException )
   {
      cerr << "Exception occurred: " 
         << memoryAllocationException.what() << endl;
   } // end catch
   
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
