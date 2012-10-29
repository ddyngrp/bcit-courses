// Steffen L. Norgren, A00683006
//
// Assignment 07 - main.cc - Question 8.16
// ---------------------------------------------------------------------

#include "DeckOfCards.h" // DeckOfCards class definition

int main()
{
	DeckOfCards deckOfCards; // create DeckOfCards object

	// Shuffle the deck 10000 times
	for ( int shuffles = 0; shuffles < 10000; shuffles++ )
	{
		deckOfCards.shuffle(); // shuffle the cards in the deck
	}
	
	deckOfCards.deal(); // deal the cards in the deck
	return 0; // indicates successful termination
} // end main
