// Steffen L. Norgren, A00683006
//
// Assignment 07 - DeckOfCards.cc - Question 8.16
// ---------------------------------------------------------------------

#include <iostream>
using std::cout;
using std::left;
using std::right;

#include <iomanip>
using std::setw;

#include <cstdlib> // prototypes for rand and srand
using std::rand;
using std::srand;

#include <ctime> // prototype for time
using std::time;

#include "DeckOfCards.h" // DeckOfCards class definition

// DeckOfCards default constructor initializes deck
DeckOfCards::DeckOfCards()
{
	// loop through rows of the deck
	for ( int row = 0; row <= 3; row++ )
	{
		// loop through columns of the deck for current row
		for ( int column = 0; column <= 12; column++ )
		{
			// Simple math to fill the array with cards from 1 to 52
			deck[ row ][ column ] = ( row * 13 + 1 + column );
		}
	}
	
	srand( time( 0 ) ); // seed random number generator
} // end DeckOfCards default constructor

// shuffle cards in deck
void DeckOfCards::shuffle()
{
	int newRow;
	int newColumn;
	int oldCard;
	int newCard;

	for ( int row = 0; row <= 3; row++ ) 
	{
		for ( int column = 0; column <= 12; column++ )
		{
			newRow = rand() % 4;
			newColumn = rand() % 13;
			
			// Storing card numbers from old and new locations
			oldCard = deck[ row ][ column ];
			newCard = deck[ newRow ][ newColumn ];
			
			// Swapping the values
			deck[ row ][ column ] = newCard;
			deck[ newRow ][ newColumn ] = oldCard;			
		}
	}
} // end function shuffle

// deal cards in deck
void DeckOfCards::deal()
{
	// initialize suit array
	static const char *suit[ 4 ] = 
		{ "Hearts", "Diamonds", "Clubs", "Spades" };

	// initialize face array
	static const char *face[ 13 ] = 
		{ "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", 
		"Eight", "Nine", "Ten", "Jack", "Queen", "King" };

	// for each of the 52 cards
	for ( int card = 1; card <= 52; card++ )
	{
		// loop through rows of deck
		for ( int row = 0; row <= 3; row++ )
		{
			// loop through columns of deck for current row
			for ( int column = 0; column <= 12; column++ )
			{
				// if slot contains current card, display card
				if ( deck[ row ][ column ] == card ) 
				{
					cout << setw( 5 ) << right << face[ column ] 
						<< " of " << setw( 8 ) << left << suit[ row ]
						<< ( card % 2 == 0 ? '\n' : '\t' );
					break; // break the loop when card is found
				} // end if
			} // end innermost for
		} // end inner for
	} // end outer for
} // end function deal
