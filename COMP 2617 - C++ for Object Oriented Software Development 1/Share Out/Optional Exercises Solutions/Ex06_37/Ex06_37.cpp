// Exercise 6.37 Solution: Ex06_37.cpp
// Help user practice multiplication; 
// check user's progress every 10 responses.
#include <iostream> 
using std::cin; 
using std::cout; 
using std::endl; 

#include <cstdlib>
using std::rand;
using std::srand;

#include <ctime>
using std::time;

void multiplication(); // function prototype
void correctMessage(); // function prototype
void incorrectMessage(); // function prototype
bool needHelp( int, int ); // function prototype

int main()
{
   srand( time( 0 ) ); // seed random number generator
   multiplication(); // begin multiplication practice
   return 0; // indicate successful termination
} // end main

// multiplication produces pairs of random numbers and
// prompts user for product
void multiplication()
{
   int x; // first factor
   int y; // second factor
   int response = 0; // user response for product
   int correct = 0; // total number of correct responses 
   int incorrect = 0; // total number of incorrect responses
   int count = 0; // count for every 10 responses

   // use sentinel-controlled repetition
   cout << "Enter -1 to End." << endl;

   // loop until sentinel value read from user
   while ( response != -1 ) 
   {
      x = rand() % 10; // generate 1-digit random number
      y = rand() % 10; // generate 1-digit random number

      cout << "How much is " << x << " times " << y << " (-1 to End)? ";
      cin >> response;
      count++; // update total number of responses

      // loop until sentinel value or correct response
      while ( response != -1 && response != x * y ) 
      {
         incorrect++; // update total number of incorrect responses

         if ( !( count % 10 ) ) // if 10 responses, check progress
         {
            // if < 75% right, terminate program
            if ( needHelp( correct, incorrect ) )
               return;

            count = 0; // clear count
         } // end if

         incorrectMessage();
         cin >> response;  
         count++; // update total number of responses
      } // end while

      if ( response == x * y ) // correct response
      {
         correct++; // update total number of correct responses

         if ( !( count % 10 ) ) // if 10 responses, check progress
         {
            // if < 75% right, terminate program
            if ( needHelp( correct, incorrect ) )
               return;

            count = 0; // clear count
         } // end if
 
         correctMessage();
      } // end if
   } // end while

   cout << "That's all for now. Bye." << endl;
} // end function multiplication

// correctMessage randomly chooses response to correct answer
void correctMessage()
{
   // generate random number between 0 and 3
   switch ( rand() % 4 ) 
   {
      case 0:
         cout << "Very good!";
         break;
      case 1:
         cout << "Excellent!";
         break;
      case 2:
         cout << "Nice work!";
         break;
      case 3:
         cout << "Keep up the good work!";
         break;
   } // end switch

   cout << endl << endl;
} // end function correctMessage

// incorrectMessage randomly chooses response to incorrect answer
void incorrectMessage()
{
   // generate random number between 0 and 3
   switch ( rand() % 4 ) 
   {
      case 0:
         cout << "No. Please try again.";
         break;
      case 1:
         cout << "Wrong. Try once more.";
         break;
      case 2:
         cout << "Don't give up!";
         break;
      case 3:
         cout << "No. Keep trying.";
         break;
   } // end switch

   cout << endl << "? ";
} // end function incorrectMessage

// needHelp returns true if < 75% right
bool needHelp( int right, int wrong ) 
{
   // if < 75% right
   if ( static_cast< double > ( right ) / ( right + wrong ) < .75 ) 
   {
      cout << "Please ask your instructor for extra help." << endl;
      return true;
   } // end if
   else // otherwise, return false
      return false;
} // end function needHelp

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
