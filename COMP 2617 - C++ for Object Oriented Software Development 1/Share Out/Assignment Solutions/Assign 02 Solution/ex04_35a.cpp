/*  
    Assignment 2 Part A
    Purpose:  Compute n factorial
	Author:   Bob Langelaan
	Date:     Oct 13, 2006
*/

#include <iostream>

using std::cout;
using std::endl; 
using std::cin; 

int main()
{
// Initialize
   int count = 2,			// count will be used to help compute factorial
	   number;				// number will contain input for which
							//      factorial is to be computed
   long long factorial = 1;		// result of n! will be stored in factorial

// Input value to compute factorial for
   cout << "Enter a positive integer less than or equal to 20: ";
   cin >> number;
   while ( (number < 0) || (number > 20) ) {
	   cout << "Enter a positive integer less than or equal to 20: ";
	   cin >> number;
   }

// Compute factorial
   while ( count  <= number ){
      factorial *= count++;
   }

// Display results
   cout << "\n" << number << "! is " << factorial << '\n' << endl;

   system("pause"); // To allow us to view the output before the console window dissappears
   return 0;
}

