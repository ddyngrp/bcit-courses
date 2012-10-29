// Exercise 8.12: Ex08_12.cpp
// Card shuffling and dealing program.
#include "DeckOfCards.h" // DeckOfCards class definition

int main()
{
   DeckOfCards deckOfCards; // create DeckOfCards object
   
   deckOfCards.shuffle(); // shuffle the cards in the deck
   deckOfCards.deal(); // deal the cards in the deck

   // checks if hand equal one of these:
   deckOfCards.pair();
   deckOfCards.threeOfKind();
   deckOfCards.fourOfKind();
   deckOfCards.flushHand();
   deckOfCards.straightHand();
   return 0; // indicates successful termination
} // end main
