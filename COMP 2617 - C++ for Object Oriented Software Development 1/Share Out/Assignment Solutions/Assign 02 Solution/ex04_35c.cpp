/*  
    Assignment 2 Part C
    Purpose:  Compute e to the power x
	Author:   Bob Langelaan
	Date:     Oct 13, 2006
*/

// With this solution, it is possible to compute thousands of terms when
//      computing e**x for 5 before overflow/underflow
//      occurs (but only 42 terms are needed to compute to the accuracy required).

#include <iostream>

 using std::cout; 
 using std::endl; 
 using std::cin; 
 using std::ios;

#include <iomanip> 
 using std::setw; 
 using std::setprecision; 
 using std::setiosflags;

int main()
{
   // Initialize
   long termCount = 1;  // the # of terms computed so far
		
   double	e = 1.0,	// contains the series sum
			term = 1.0, // contains the term value
		    x;		    // the value for which e**x is to be computed	

/* Stay in do-while loop below until user enters valid 
	value for 'x'. */
   do {  
	   cout << "Input a value for x between 1 and 156: ";
	   cin >> x;
   } while ((x<1)||(x>156));
   
/* In the while loop below we calculate the next term and then
   add the term just calculated to the series sum. 
   
   Note that if we start with the previous term, we can compute
   the next term by simply multiplying by x and dividing by 
   term_count

   Note that with each iteration of the while loop, the value of term 
   eventually gets smaller and smaller (not true for the first few iterations)
   We exit the while loop when term becomes less than 1.0E-20 (a very small value)

*/
   while ( term > 1.0E-20 ) {  
      term = term * (x / termCount++);
      e += term;
   }

   // Now output the computed series sum
   cout << endl << setiosflags( ios::fixed | ios::showpoint )
        << setprecision( 2 ) << "e raised to the " << x << " power is "
        << setprecision( 10 ) << e << endl;

   // Output how many terms needed to get to required accuracy
   cout << "\nThe number of terms computed is "
	    << termCount << '\n' << endl;

   system("pause"); // To allow us to view the output before the console window dissappears
   return 0;
}

