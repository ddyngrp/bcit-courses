/*  
    Assignment 2 Part B
    Purpose:  Compute an approximate value for e
	Author:   Bob Langelaan
	Date:     Oct 13, 2006
*/

#include <iostream>

using std::cout;
using std::cin;
using std::endl; 

#include <iomanip>

using std::setprecision;

int main()
{
// Initialize
   long long factorial = 1,	// Used to store factorial value
	   numberOfTerms;		// Used to store # of terms user wants program to compute

   double e = 1.0,		 // Used to store computed approximation for e
	   oneValue = 1.0;   // Used to represent 1.0 as a double

// Have user input number of terms to compute
   do {
        cout << "The number of terms to compute is (5 to 13 are valid values): ";
        cin >> numberOfTerms;
   } while (numberOfTerms < 5 || numberOfTerms > 13);

// Compute the value of e in a for loop
   for (int count = 1; count < numberOfTerms; ++count) {
      factorial *= count;
      e += oneValue / factorial;
   }

// Display the result
   cout << setprecision(12) << "\nThe value of e is " << e << '\n' << endl;

   system("pause"); // To allow us to view the output before the console window dissappears
   return 0;
}
