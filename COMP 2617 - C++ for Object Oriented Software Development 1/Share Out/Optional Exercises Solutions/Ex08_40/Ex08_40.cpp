// Exercise 8.40 Solution: Ex08_40.cpp
#include <iostream> 
using std::cin; 
using std::cout; 
using std::endl; 

// prototype
unsigned long stringLength1( const char * );
unsigned long stringLength2( const char * );

int main()
{
   char string[ 100 ];

   cout << "Enter a string: ";
   cin >> string;

   cout << "\nAccording to stringLength1 the string length is: "
      << stringLength1( string ) 
      << "\nAccording to stringLength2 the string length is: "
      << stringLength2( string ) << endl;

   return 0; // indicate successful termination
} // end main

// finding string length using arrays
unsigned long stringLength1( const char *sPtr )
{
   // array subscript notation
   for ( int length = 0; sPtr[ length ] != '\0'; length++ )
      ; // empty body

   return length;
} // end function stringLength1

// finding string length using pointers
unsigned long stringLength2( const char *sPtr )
{
   // pointer notation
   for ( int length = 0; *sPtr != '\0'; sPtr++, length++ )
      ; // empty body

   return length;
} // end function stringLength2
