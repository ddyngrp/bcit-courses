/* Created by Anjuta version 1.2.4 */
/*	This file will not be overwritten */

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <cstring>
using std::strcmp;
using std::strlen;


int main()
{
	
	char s1[ 20 ];
	char s2[ 20 ];
	int stringLength;
	
	cout << "Enter the first string: ";
	cin.getline( s1, '\n' );
	
	cout << "Enter the second string: ";
	cin.getline( s2, '\n' );
	
	if ( strlen( s1 ) >= strlen( s2 ) )
		stringLength = strlen( s2 );
	else
		stringLength = strlen( s1 );

	
	if ( strncmp( s1, s2, stringLength ) < 0 )
		cout << endl << s1 << " is less than " << s2 << endl;
	
	if ( strncmp( s1, s2, stringLength ) > 0 )
		cout << endl << s1 << " is greater than " << s2 << endl;
	
	if ( strncmp( s1, s2, stringLength ) == 0 )
		cout << endl << s1 << " is equal to " << s2 << endl;
	
	return 0;
}
