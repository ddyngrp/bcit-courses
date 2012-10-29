/*

Write a program that uses the C string library strncmp() function to 
compare two strings input by the user. The number of characters to be 
compared by the strnncmp() function should be equal to the length of 
the shortest string that is input by the user (you may assume that the 
user will always input a string 2 or more characters in length). 
The program should state whether the first input string is less than, 
equal to, or greater than the second input string. 

*/

#include <cstring>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void main( void )
{
   char String1[80],  // used to store the first input string
        String2[80];  // used to store the second input string

   long len1,	 // used to store the length of the first string
	    len2,    // used to store the length of the second string
        lencmp;  // will be the 3rd arguement to the strncmp() function

   char tmp[20]; // used to store string 
   long result;  // used to store result of strncmp() function

// Have user input two strings

   cout << "Input the first string: \n\n";
   cin.getline( String1,80,'\n');

   cout << "\nInput the second string: \n\n";
   cin.getline( String2,80,'\n');

// Use the strlen function to find out length of the two strings

   len1 = strlen( String1 );
   len2 = strlen( String2 );

   if (len1 < len2)
	   lencmp = len1;  // the first string is the shorter than the second string
   else
       lencmp = len2;  // the second string is shorter or equal in length to first string

// Output results

   cout << "\nCompare strings:\n\t\t" << String1 << "\n\t\t" << String2 << "\n\n";
 
   result = strncmp( String1, String2 , lencmp );
   
   if( result > 0 )
      strcpy( tmp, "greater than" );
   else if( result < 0 )
      strcpy( tmp, "less than" );
   else
      strcpy( tmp, "equal to" );

   cout << "Result:\t\tString 1 is " << tmp << " String 2\n\n";

   system("pause"); // To allow us to view the output before the console window dissappears

}

