// Assignment 3 Solution: Ex06_36.cpp
// Help user practice multiplication.
// 
// Bob Langelaan
// Feb. 10, 2007

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

int main()
{
   srand( time( 0 ) ); // seed random number generator
   multiplication(); // begin multiplication practice

   system("pause");  // enter any character to exit
   return 0; // indicate successful termination
} // end main

// multiplication produces pairs of random numbers and
// prompts user for product
void multiplication()
{
   int x; // first factor
   int y; // second factor
   int response = 0; // user response for product

   // use sentinel-controlled repetition
   cout << "Enter -1 to End." << endl;

   // loop until sentinel value read from user
   while ( response != -1 ) 
   {
      x = rand() % 10; // generate 1-digit random number
      y = rand() % 10; // generate 1-digit random number

      cout << "How much is " << x << " times " << y << " (-1 to End)? ";
      cin >> response;

      // loop until sentinel value or correct response
      while ( (response != -1) && (response != (x * y)) ) 
      {
         incorrectMessage();
         cin >> response;
      } // end while

      if ( response == (x * y) ) // correct response
         correctMessage();
   } // end while

   cout << "\nThat's all for now. Bye." << endl;
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
