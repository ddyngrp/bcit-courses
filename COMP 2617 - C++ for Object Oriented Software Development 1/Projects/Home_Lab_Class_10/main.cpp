// Home Lab 10 - Question 8.43: main.cpp
// Author: Steffen L. Norgren
// Date: March 22nd, 2007

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <cstring>
using std::strtok;
using std::strcmp;

int main()
{
	char datestring[ 80 ];
	char *tokenPtr;
	
	// initialize month array
	static const char *month[ 12 ] = 
		{ "January", "February", "March", "April", "May", "June", "July", 
		"August", "September", "October", "November", "December" };

	// initialize month number array
	static const char *monthNum[ 12 ] = 
		{ "01", "02", "03", "04", "05", "06", "07", 
		"08", "09", "10", "11", "12" };
		
	cout << "Input a date in the format of 07/21/1955: ";
	cin >> datestring;
				
	// Month Section
	tokenPtr = strtok( datestring, "/" );
	
	for ( int i = 0; i < 12; i++ )
	{
		if ( strcmp( tokenPtr, monthNum[ i ] ) == 0 )
			cout << '\n' << month[ i ] << " ";
	}
			
	// Day Section
	tokenPtr = strtok( NULL, "/" );

	cout << tokenPtr << ", ";

	// Year Section
	tokenPtr = strtok( NULL, "/" );
	
	cout << tokenPtr << endl;

    return 0;
}