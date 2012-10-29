// Assign 6 Solution
// File Name: Assign06.cpp
// Author: Bob Langelaan
// Date: Feb. 18th, 2006

/*  This application inputs 20 numbers and adds only the unique ones 
    to an array called UniqueNos.  Each time a number is found to
	be unique it is displayed as well.                                  */

#include <iostream> 

using std::cout;
using std::cin;
using std::endl;

#include <iomanip>
using std::setw;

/* The main program performs all functions in this application */

int main()
{

	// Declare and initialize variables

   int UniqueNos[20],        //  used to store up to 20 unique #s
	   NextNumber,           //  used to store the next number read in.
	   ArrayPosition = -1;   //  points to current position in array UniqueNos where
                             //       last unique number was stored

   int LoopCounter; // used as loop counter below

   bool Found;  // Boolean flag used to signal if number unique or not

   // The following loop is used to input the 20 numbers

   for ( int I = 1; I <= 20; ++I )
   {
		Found = false;  // Start loop each time with bool flag signalling we did not find 
		                //    the next number input in the UniquNos array.

		cout << "\nEnter # " << I << " : ";
		cin >> NextNumber;
		while (NextNumber < 10 || NextNumber > 100)
		{
			cout << "The number enetered is not in the valid range of 10 to 100" << endl;
			cout << "\nEnter # " << I << " : ";
			cin >> NextNumber;
		}

		/* The following while loop checks to see if NextNumber is unique by checking
		   if it is already in the UniqueNos array.                                 */

		LoopCounter = 0;
		while (LoopCounter <= ArrayPosition) 
		{
			if (UniqueNos[LoopCounter] == NextNumber)
			{
				Found = true;  // Signal we found that number is already in array UniqueNos
				break;     // We can exit loop, since we found it in the array.
			}
			++LoopCounter;
		}

		if (!Found) // If NextNumber was NOT found in the UniqueNos array
		{
			UniqueNos[++ArrayPosition] = NextNumber;  // point to next location in array 
			                                          //   and save new value in array
			cout << "The number: "  << NextNumber << " is unique" << endl;
		}
   }

   // Output Results
   cout << "\n\nThe unique numbers are:\n\n";

   for (int lcounter = 0; lcounter <= ArrayPosition; ++lcounter){
	   cout << setw(6) << UniqueNos[lcounter];
	   if (lcounter % 5 == 4){
		   cout << '\n';
	   }
   }

   // Wait for signal to go home
   cout << '\n' << endl;
   system("pause");

   // Time to go home

   return 0;
}


