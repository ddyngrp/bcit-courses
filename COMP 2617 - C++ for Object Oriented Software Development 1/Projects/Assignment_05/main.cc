// Steffen L. Norgren, A00683006
//
// Assignment 05 - main.cc
// ---------------------------------------------------------------------

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <iomanip>
using std::setw;

// Function prototypes
int checkValues( int );
int isUnique( int [], int, int );
void printArray( int [], int );

int main()
{
	static int arraySize = 20; // size of the array
	int a[ arraySize ]; // initialize array
	
	for ( int i = 0; i < arraySize; i++ )
	{
		a[ i ] = isUnique( a, checkValues( i ), i );
		
		if ( a[ i ] != 0 )
			cout << "The number: " << a[ i ] << " is unique" << endl;
	}

	printArray( a, arraySize );
	
	return 0;
}

// Checking the input against the array such that we know whether
// the value is unique or within the valid range.
int checkValues( int elementID )
{
	int input;
	
	do
	{
		cout << "\nEnter # " << elementID + 1 << " : ";
		cin >> input;
		
		if ( input < 10 || input > 100 )
		{
			cout << "The number entered is not in the valid range of 10 to 100";
			cout << endl;
		}
	} while ( input < 10 || input > 100 );
	
	return input;
}

// Checking if the value is unique within the array. If not, it will return
// zero, which the print function will ignore when printing the results.
// Will only search through to the current ElementID for efficiency.
int isUnique( int a[], int arrayInput, int maxElementID )
{
	for ( int j = 0; j < maxElementID; j++ )
		if ( a[ j ] == arrayInput ) // if the input is not unique
			return 0;

	return arrayInput;
}

// Function to print the array. This will ignore all elements with the
// value of zero.
void printArray( int a[], int sizeOfArray )
{
	cout << endl << "\nThe unique numbers are:\n" << endl;
	
	int columnNum = 1;
	
	for ( int i = 0; i < sizeOfArray; i++ )
	{
		if ( a[ i ] != 0 ) // doesn't print out when the element is 0
		{
			cout << setw( 4 ) << a[ i ];
			
			if ( columnNum % 5 == 0 )
				cout << "\n";
			
			columnNum++;
		}
	}
}
