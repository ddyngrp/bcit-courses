// Exercise 8.36 Solution: Ex08_36.cpp
#include <iostream> 
using std::cin; 
using std::cout; 
using std::endl; 

#include <cstring> 
using std::strtok;

void reverseTokens( char * const ); // prototype

int main()
{
   const int SIZE = 80;
   char text[ SIZE ];
   
   cout << "Enter a line of text:\n";
   cin.getline( text, SIZE );
   
   // call to function reverseTokens
   reverseTokens( text );
   cout << endl;
   return 0; // indicate successful termination
} // end main

// function to reverse the individual tokens 
void reverseTokens( char * const sentence )
{
   char *pointers[ 50 ]; // array to store entire sentence
   char *temp; // store each word

   int count = 0; // serve as array counter
   
   // call function strtok to take first word out of sentence
   temp = strtok( sentence, " " );
   
   // while temp is not empty
   while ( temp ) 
   {
      // add the word into the array
      pointers[ count++ ] = temp;
      
      // get each subsequent word from the sentence
      temp = strtok( 0, " " );
   } // end loop
   
   cout << "\nThe tokens in reverse order are:\n";

   // loop through the array backwards 
   for ( int i = count - 1; i >= 0; i-- )
      cout << pointers[ i ] << ' ';
} // end function reverseTokens
