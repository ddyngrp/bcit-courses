// Exercise 8.12: DeckOfCards.cpp
// Member-function definitions for class DeckOfCards that simulates
// the shuffling and dealing of a deck of playing cards.
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
   char *suitValue[ 4 ] = { "Hearts", "Diamonds", "Clubs", "Spades" };
   char *faceValue[ 13 ] = { "Ace", "Deuce", "Three", "Four", "Five", 
      "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" }; 

   // initialize suit
   for ( int i = 0; i < 4; i++ )
      suit[ i ] = suitValue[ i ];

   // initialize face
   for ( int i = 0; i < 13; i++ )
      face[ i ] = faceValue[ i ];

   // loop through rows of deck
   for ( int row = 0; row <= 3; row++ )
   {
      // loop through columns of deck for current row
      for ( int column = 0; column <= 12; column++ )
      {
         deck[ row ][ column ] = 0; // initialize slot of deck to 0
      } // end inner for
   } // end outer for
   
   srand( time( 0 ) ); // seed random number generator
} // end DeckOfCards default constructor

// shuffle cards in deck
void DeckOfCards::shuffle()
{
   int row; // represents suit value of card
   int column; // represents face value of card

   // for each of the 52 cards, choose a slot of the deck randomly
   for ( int card = 1; card <= 52; card++ ) 
   {
      do // choose a new random location until unoccupied slot is found
      {                                                                   
         row = rand() % 4; // randomly select the row
         column = rand() % 13; // randomly select the column
      } while( deck[ row ][ column ] != 0 ); // end do...while

      // place card number in chosen slot of deck
      deck[ row ][ column ] = card;
   } // end for
} // end function shuffle

// deal a five card poker hand
void DeckOfCards::deal()
{
   int r = 0;

   cout << "The hand is:\n";

   // loop to distrubute the cards
   for ( int card = 1; card < 6; card++ )

      for ( int row = 0; row <= 3; row++ )

         for ( int column = 0; column <= 12; column++ )

            if ( deck[ row ][ column ] == card ) 
            {
               hand[ r ][ 0 ] = row;
               hand[ r ][ 1 ] = column;
               cout << setw( 5 ) << face[ column ] << " of "  
                  << setw( 8 ) << left << suit[ row ] 
                  << ( card % 2 == 0 ? '\n' : '\t' ) << left;
               r++;
            } // end if

   cout << '\n';
} // end function deal

// pair determines if the hand contains one or two pair
void DeckOfCards::pair()
{
   int counter[ 13 ] = { 0 };

   // check 
   for ( int r = 0; r < 5; r++ )
      counter[ hand[ r ][ 1 ] ]++;

   cout << '\n';

   // print result if there is a pair
   for ( int p = 0; p < 13; p++ )

      if ( counter[ p ] == 2 )
        cout << "The hand contains a pair of " << face[ p ] << "'s.\n";
}  // end function pair

// check if three of a kind 
void DeckOfCards::threeOfKind()
{
   int counter[ 13 ] = { 0 };

   for ( int r = 0; r < 5; r++ )
      counter[ hand[ r ][ 1 ] ]++;

   for ( int t = 0; t < 13; t++ )

      if ( counter[ t ] == 3 )
         cout << "The hand contains three " << face[ t ] << "'s.\n";
}  // end function threeOfKind

// check if four of a kind
void DeckOfCards::fourOfKind()
{
   int counter[ 13 ] = { 0 };

   for ( int r = 0; r < 5; r++ )
      counter[ hand[ r ][ 1 ] ]++;

   for ( int k = 0; k < 13; k++ )

      if ( counter[ k ] == 4 )       
         cout << "The hand contains four " << face[ k ] << "'s.\n";
} // end function fourOfKind

// check for a flush
void DeckOfCards::flushHand()
{
   int count[ 4 ] = { 0 };

   for ( int r = 0; r < 5; r++ )
      count[ hand[ r ][ 0 ] ]++;

   for ( int f = 0; f < 4; f++ )

      if ( count[ f ] == 5 )
         cout << "The hand contains a flush of " << suit[ f ] << "'s.\n";
} // end function flushHand

// check the hand dealt
void DeckOfCards::straightHand()
{
   int s[ 5 ] = { 0 }; // to hold a copy of wHand
   int temp;

   // copy column locations to sort
   for ( int r = 0; r < 5; r++ )
      s[ r ] = hand[ r ][ 1 ];

   // bubble sort column locations
   for ( int pass = 1; pass < 5; pass++ )

      for ( int comp = 0; comp < 4; comp++ )

         if ( s[ comp ] > s[ comp + 1 ] ) 
         {
            temp = s[ comp ];
            s[ comp ] = s[ comp + 1 ];
            s[ comp + 1 ] = temp;
         } // end if

   // check if sorted columns are a straight
   if ( s[ 4 ] - 1 == s[ 3 ] && s[ 3 ] - 1 == s[ 2 ] 
      && s[ 2 ] - 1 == s[ 1 ] && s[ 1 ] - 1 == s[ 0 ] ) 
   {
      cout << "The hand contains a straight consisting of\n";
            
      for ( int j = 0; j < 5; j++ )
         cout << face[ hand[ j ][ 1 ] ] << " of " 
            << suit[ hand[ j ][ 0 ] ] << '\n';
   } // end if
} // end function straightHand
