// Steffen L. Norgren, A00683006
//
// Assignment 03 - Exercise 6.36 Solution: main.cc
// ---------------------------------------------------------------------

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <cstdlib>	// Contains prototypes for functions rand
using std::rand;
using std::srand;	// Random number generator isn't quite random enough

// Function Prototypes
void multiplication();
void correctMessage();
void incorrectMessage();

// function main begins program execution
int main()
{
	multiplication();
	return 0;
}

// This is where most of the action happens. We get user input,
// multuply the factors and compare against input.
void multiplication()
{
	int factorX;
	int factorY;
	int productXY;
	int input = 0;
	
	cout << "Welcome to the multiplication tryouts!" << endl;
	cout << "When finished, enter -1 to quit the program.\n" << endl;
	
	// Have the user enter the results to the question until
	// they enter -1
	while ( input != -1 )
	{
		// randomizing the random number generator by using the system
		// time as the random number generator's seed.
		srand( time( 0 ) );
		
		// Standard multiplication tables include numbers from 1 to 12
		// as such, I will do the same with this program.
		factorX = 1 + rand() % 12;
		factorY = 1 + rand() % 12;
		productXY = factorX * factorY;
		
		cout << "How much is " << factorX << " times " << factorY << " ? ";
		cin >> input;
		
		// Check whether the input agrees with the product and display
		// a message accordingly.
		if ( productXY == input )
			correctMessage();
		else
			incorrectMessage();
		
	} // end while loop
}

// If the user inputs the correct answer this function is called
void correctMessage()
{
	int messageNumber;
	
	messageNumber = 1 + rand() % 4; // Randomize the message
	
	// Return a message based on the result of messageNumber
	switch ( messageNumber )
	{
		case 1:
			cout << "Very good!\n" << endl;
			break;
		case 2:
			cout << "Excellent!\n" << endl;
			break;
		case 3:
			cout << "Nice work!\n" << endl;
			break;
		case 4:
			cout << "Keep up the good work!\n" << endl;
			break;
		default: // Something is very wrong
			cout << "The laws of physics have been violated!" << endl;
	}
}

// If the user inputs the incorrect answer this function is called
void incorrectMessage()
{
	int messageNumber;
	
	messageNumber = 1 + rand() % 4; // Randomize the message
	
	// Return a message based on the result of messageNumber
	switch ( messageNumber )
	{
		case 1:
			cout << "No. Please try again.\n" << endl;
			break;
		case 2:
			cout << "Wrong. Try once more.\n" << endl;
			break;
		case 3:
			cout << "Don't give up!\n" << endl;
			break;
		case 4:
			cout << "No. Keep trying.\n" << endl;
			break;
		default: // Something is very wrong
			cout << "This program has been violated, calling 911..." << endl;
	}	
}
