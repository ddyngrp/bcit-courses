// Steffen L. Norgren, A00683006
//
// Assignment 07 - DeckOfCards.h - Question 8.16
// ---------------------------------------------------------------------

// DeckOfCards class definition

class DeckOfCards
{
public:
   DeckOfCards(); // constructor initializes deck
   void shuffle(); // shuffles cards in deck
   void deal(); // deals cards in deck
private:
   int deck[ 4 ][ 13 ]; // represents deck of cards
}; // end class DeckOfCards
