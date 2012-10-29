// Exercise 8.35 Solution: Ex08_35.cpp
#include <iostream> 
using std::cin; 
using std::cout; 
using std::endl; 

#include <cstring> 
using std::strtok;

#include <cstdlib>

int main()
{
   const int SIZE1 = 20;
   const int SIZE2 = 10;
   
   char p[ SIZE1 ];
   char phoneNumber[ SIZE2 ] = { '\0' };
   
   char *tokenPtr; // store temporary token
   char *areaCode; // store area code
   char *phone; // store the phone number
   
   cout << "Enter a phone number in the form (555) 555-5555:\n";
   cin.getline( p, SIZE1 );
   
   // pick apart the area code from the entire string
   areaCode = strtok( p, "()" );
   
   // function strtok to take the next token in the string
   tokenPtr = strtok( 0, "-" );

   // copies the result from the second call to strtok into phoneNumber
   strcpy( phoneNumber, tokenPtr );

   // the last call to strtok to take the last 4 digits
   tokenPtr = strtok( 0, "" );

   // concatenate the result with the current phoneNumber
   strcat( phoneNumber, tokenPtr );

   phone = phoneNumber;
   
   cout << "\nThe area code is " << areaCode 
      << "\nThe phone number is " << phone << endl;

   return 0; // indicates successful termination
} // end main
