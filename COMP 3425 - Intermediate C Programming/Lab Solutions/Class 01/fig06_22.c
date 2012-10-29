// Fig. 6.22: fig06_22.cpp
// Using default arguments.
/*
#include <iostream>
using std::cout;
using std::endl;
*/

#include <stdio.h>
#include <stdlib.h>

// function prototype that specifies default arguments
int boxVolume( int length, int width, int height );

int main()
{
   // no arguments--use default values for all dimensions
   printf("The default box volume is: %d", boxVolume(1,1,1));
   
   // specify length; default width and height
   printf("\n\nThe volume of a box with length 10,\n");
   printf("width 1 and height 1 is: %d",boxVolume( 10, 1, 1 ));
        
   // specify length and width; default height
   printf("\n\nThe volume of a box with length 10,\n");
   printf("width 5 and height 1 is: %d",boxVolume( 10, 5, 1 ));
   
   // specify all arguments 
   printf("\n\nThe volume of a box with length 10,\n");
   printf("width 5 and height 2 is: %d\n",boxVolume( 10, 5, 2 ));

   system("pause");
   return 0; // indicates successful termination
} // end main

// function boxVolume calculates the volume of a box
int boxVolume( int length, int width, int height )
{ 
   return length * width * height;
} // end function boxVolume


/**************************************************************************
 * (C) Copyright 1992-2005 by Deitel & Associates, Inc. and               *
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
