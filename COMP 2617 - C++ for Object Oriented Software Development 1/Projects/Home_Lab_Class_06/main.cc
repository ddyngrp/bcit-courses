/* Created by Anjuta version 1.2.4 */
/*	This file will not be overwritten */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "min.h"

int main()
{
	int intValue1;
	int intValue2;
	double doubleValue1;
	double doubleValue2;
	char charValue1;
	char charValue2;
	
	// Integer Values
	cout << "\nInput the first integer value: ";
	cin >> intValue1;
	
	cout << "\nInput the second integer value: ";
	cin >> intValue2;
	
	cout << "\nThe smaller of the two integer values is: ";
	cout << min( intValue1, intValue2 ) << endl;

	// Floating point values
	cout << "\nInput the first floating point value: ";
	cin >> doubleValue1;
	
	cout << "\nInput the second floating point value: ";
	cin >> doubleValue2;
	
	cout << "\nThe smaller of the two floating point values is: ";
	cout << min( doubleValue1, doubleValue2 ) << endl;

	// Char Values
	cout << "\nInput the first char value: ";
	cin >> charValue1;
	
	cout << "\nInput the second char value: ";
	cin >> charValue2;
	
	cout << "\nThe smaller of the two char values is: ";
	cout << min( charValue1, charValue2 ) << endl;
	
	return 0;
}
