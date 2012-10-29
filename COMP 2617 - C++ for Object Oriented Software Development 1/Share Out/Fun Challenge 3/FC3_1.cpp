/* Exercise 7.29 Solution */
/* Less efficient algorithm provided by publisher */
/* Modified slightly by Bob Langelaan */
/* Date: March 27, 2006  */

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;
using std::setprecision;

#include <ctime>
using std::time;

#define SIZE 100000 //will support a value of 1 million

int main()
{ 
   char array[ SIZE ]; /* array to indicate prime numbers */
   long loop;          /* loop counter */
   long loop2;         /* loop counter */
   long count = 0;     /* total prime numbers */

   time_t start_time;    /* used to store starting time */
   time_t end_time;      /* used to store end time */
   time_t total_time;    /* used to compute total time to compute solution */

   start_time = time(NULL); // record start time

   /* set all array elements to 1 */
   for ( loop = 0; loop < SIZE; loop++ ) {
      array[ loop ] = 1;
   } /* end for */

   /* test for multiples of current subscript */
   for ( loop = 2; loop < SIZE; loop++ ) {

      /* start with array subscript two */
      if ( array[ loop ] == 1 ) {

         /* loop through remainder of array */
         for ( loop2 = loop+1; loop2 < SIZE; loop2++ ) {

            /* set to zero all multiples of loop */
            if ( loop2 % loop == 0 ) {
               array[ loop2 ] = 0;
            } /* end if */

         } /* end for */

      } /* end if */

   } /* end for */

   end_time = time(NULL); // record end time
   total_time = end_time - start_time; // calculate time to compute primes

   /* display prime numbers in the range 2 - 197 */
   for ( loop = 2; loop < SIZE; loop++ ) {

      if ( array[ loop ] == 1 ) { 
		 cout << setw(8) << loop << " is a prime number\n";
         ++count;
      } /* end if */

   } /* end for */

   cout << "\nA total of " << count << " prime numbers were found\n";
   cout << "that are less than "<< SIZE;

   cout << "\n\nIt took " << static_cast<long>(total_time) << " seconds to compute the solution\n" << endl;

   system("pause");  // ask user if ok to go away

   return 0; /* indicate successful termination */

} /* end main */



 /*************************************************************************
 * (C) Copyright 1992-2004 by Deitel & Associates, Inc. and               *
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
