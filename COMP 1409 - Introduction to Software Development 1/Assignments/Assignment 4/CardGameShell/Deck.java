import java.util.Random;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Arrays;

/**
 * Deck class. This represents a single deck of DECK_SIZE cards. This class has
 * several "stub" methods with comments and signatures. Feel free to add other
 * methods as you see fit. Suggestion: private void swap(int fistCard, int secondCard)
 * The suggested swap() method would function as a helper to the shuffle() method.
 * 
 * @author Colleen Penrowley 
 * @version Fall 2005 modified Fall 2006
 */
public class Deck  
{
    public static final int DECK_SIZE = 52;             // The number of cards in a deck
    public static final int SUITS_IN_DECK = 4;          // The number of suits in a deck
    public static final int CARDS_IN_SUIT = 13;         // The number of cards in a suit
    public static final int TIMES_TO_SHUFFLE = 10000;   // The number of times to shuffle
    
    private ArrayList<Card> deck;                       // a deck of cards

    // Array holding the suit names
    private static final String[] suitNameArray = { "Diamonds", "Hearts", "Clubs", "Spades" };
    // Array holding the card descriptions
    private static final String[] cardNameArray = { "Two", "Three", "Four", "Five", 
                                                    "Six", "Seven", "Eight", "Nine", "Ten",
                                                    "Jack", "Queen", "King", "Ace" };
    // Array holding the card values
    private static final int[] cardValueArray = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, Game.ACE_HIGH_VALUE };
    
    /**
     * Constructor for objects of class Deck
     */
    public Deck()
    {
       deck = new ArrayList<Card>();
    }

    /**
     * Load a new deck with all SUITS_IN_DECK * CARDS_IN_SUIT size
     */
    public void newDeck()
    {
        // loops through the number of suits in the deck
        for ( int i = 0; i < SUITS_IN_DECK; i++ )
        {
            // loops through the number of cards in a suit
            for ( int j = 0; j < CARDS_IN_SUIT; j++ )
            {
                // uses the values from the static arrays to populate the card objects
                addCard( new Card( cardNameArray[j], suitNameArray[i], cardValueArray[j] ) );
            } // end inner loop
        } // end outer loop
    }

    /**
     * Add a single card to the deck.
     * @param a Card object
     */
    public void addCard( Card newCard )
    {
        // add a new Card object to the deck ArrayList
        deck.add( newCard );
    }
    
    /**
     * Shuffle the deck. This involves selecting random pairs of 
     * cards and swapping them, the number of times to swap determined
     * by the constant TIMES_TO_SHUFFLE. Java provides a shuffle method
     * as part of the Collections interface, however for this assignment
     * you must write your own.
     */
    public void shuffle()
    {
        Random rand = new Random(); // Default seed comes from system time
        
        // initiates a loop that will shuffle 2 card positions TIMES_TO_SHUFFLE times
        for ( int i = 0; i < TIMES_TO_SHUFFLE; i++ )
        {
            // calls the swap method using two randomly generated numbers < DECK_SIZE
            swap( rand.nextInt( DECK_SIZE ), rand.nextInt( DECK_SIZE) );
        }
    }
    
    /**
     * Swaps two Card objects in the deck.
     * @param xCard first Card object
     * @param yCard second Card object
     */
    public void swap( int xCard, int yCard )
    {
        Card tempCard = deck.get( xCard );      // Temporary object storage for first Card object
        
        deck.set( xCard, deck.get( yCard ) );   // Sets the xCard position to the value of yCard
        deck.set( yCard, tempCard );            // Sets the yCard position to the temporary object
    }
    
    /**
     * Display the entire contents of the deck. Not used in the
     * game but useful for debugging.
     */
    public void showDeck()
    {
        // cycles through each card object stored in the deck ArrayList
        for ( Card eachCard : deck )
        {
            // uses the Card class' toString method to display the full card info as well
            // as the getValue method to display the stored value for debugging purposes
            System.out.println( eachCard.toString() + " -- Value: " + eachCard.getValue() );
        }
    }
    
    /**
     * Returns whether the deck is empty or not.
     */
    public boolean hasCards()
    {
        return !deck.isEmpty(); // inverting the result to return true if there are cards
    }
    
    /**
     * Remove the top card (the first card) from the deck.
     * @return the Card object removed or null if there is nothing in the deck.
     */
    public Card takeCard()
    {
        // check to see if there are cards in the deck
        if ( deck.size() > 0 )
        {
            Card removedCard = deck.get( 0 );   // Temporary object storage for removed Card object
            deck.remove( 0 );
            
            return removedCard;
        }
        else
        {
            // return null if the deck is empty
            return null;
        }
    }

}
