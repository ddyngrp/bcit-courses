// Exercise 8.12 Solution: DeckOfCards.h
// Definition of class DeckOfCards that 
// represents a deck of playing cards.

// DeckOfCards class definition
class DeckOfCards
{
public:
   DeckOfCards(); // constructor initializes deck
   void shuffle(); // shuffle the deck
   void deal(); // deal a five card poker hand
   void pair(); // pair determines if the hand contains one or two pair
   void threeOfKind(); // check if three of a kind
   void fourOfKind(); // check if four of a kind
   void flushHand(); // check for a flush
   void straightHand(); // check for a straight hand
private:
   int deck[ 4 ][ 13 ]; // represents deck of cards
   const char *suit[ 4 ]; // card suit
   const char *face[ 13 ]; // card face
   int hand[ 5 ][ 2 ]; // represents five-card poker hand
}; // end class DeckOfCards
