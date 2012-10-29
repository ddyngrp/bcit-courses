import java.util.ArrayList;
import java.util.Iterator;

/**
 * COMP 1409 final assignment. This is a very simple Blackjack game that does not involve betting. 
 * It is meant to be played by a single player and no dealer but could easily be extended to make it more
 * like a real Blackjack game.
 * The Game class manages the other classes that make up the application. This class has several
 * constants defined, and several suggested fields. You will need others. The play() method is 
 * what will start the game. Some private helper methods are suggested. You will need others.
 * 
 * @author Colleen Penrowley 
 * @version Fall 2005, revised Winter 2006, revised Fall 2006)
 */
public class Game
{
    /** Suggested constants for use throughout the game. To use one of these in another class, specify 
     * the Game class first, e.g. Game.ACE_LOW_VALUE.
     */
    public static final int ACE_LOW_VALUE = 1;      // bottom value for ace
    public static final int ACE_HIGH_VALUE = 11;    // top value for ace
    public static final int BLACKJACK = 21;         // instant win - to go over is to lose
  
    /* Some suggested fields */
    private Deck deck;                              // a deck of cards
    private InputReader reader;                     // keyboard reader
    private ArrayList<Card> hand;                   // the cards the player is holding
    private boolean continueGame;                   // continue playing or not
    private boolean notBustOrBlackJack;             // whether the hand goes over 21
    private boolean notStanding;                    // whether the players chose stand
    private int handValue;                          // current hand value
    private int rounds;                             // how many rounds played
    private int totalPoints;                        // total points earned
    
    /**
     * Constructor for objects of class Game
     */
    public Game()
    {
        hand = new ArrayList<Card>();               // ArrayList for the player's current hand
        reader = new InputReader();                 // Initialise the input reader
        deck = new Deck();                          // creating a new deck
        
        play();                                     // Start the game
    }
  
    /**
     * This method holds the game logic. The user is repeatedly 
     * prompted to play another round. When the user has chosen to stop 
     * playing, the final tally of wins and losses is reported.
     * 
     */
    public void play()
    {
        rounds = 0;             // set rounds to 0 since this is a fresh round
        totalPoints = 0;        // set total points to 0 since this is a fresh round
        continueGame = true;    // set to default value
        
        while ( continueGame )
        {
            System.out.print("Would you like to play a new game of BlackJack? [Yes/No] ");
            String response = reader.readInputLine().trim().toLowerCase();
            if ( response.equals("yes") )
            {
                rounds++;                   // increment the round as this is a new one
                notStanding = true;         // set back to default value after a hand
                notBustOrBlackJack = true;  // set back to default value after a hand
                hand.clear();               // empty any previous hand from the ArrayList
                dealCard();                 // deal first card
                dealCard();                 // deal second card
                showHand();                 // show the hand
                
                while ( notBustOrBlackJack && notStanding )
                {
                    playerTurn();   // start the turn
                } // end inner while
            }
            else if ( response.equals("no") )
            {
                continueGame = false;
            } // end if
        } // end while
    }
    
    /**
     * Deal one card from the deck and put it into the player's hand.
     * If the deck is empty, it will automatically create and shuffle
     * a brand new deck.
     */
    private void dealCard()
    {
        // check to see if there are cards left in the deck first
        if ( deck.hasCards() )
        {
            hand.add( deck.takeCard() );    // add a card to the current hand
        }
        else
        {
            deck.newDeck();                 // create a new deck
            deck.shuffle();                 // shuffling the new deck
            hand.add( deck.takeCard() );    // add a card to the current hand
        }
    }
    
   /**
    * Play out the player's turn.
    * The player may choose to hit or stand, unless the player's
    * cards total more than BLACKJACK, in which case the player
    * is "busted".
    */ 
    private void playerTurn()
    {
        System.out.print("Your choice: hit or stand? ");
        String response = reader.readInputLine().trim().toLowerCase();
        if ( response.equals("hit") )
        {
            dealCard();
            showHand();
        }
        else if ( response.equals("stand") )
        {
            totalGamePoints();  // calculate the points awarded for hand and add to total
            showTotals();       // print the totals out
            notStanding = false;
        }
    }
    
    /**
     * Calculates and returns the value of the hand. An ace is worth ACE_HIGH_VALUE
     * unless it would cause a "bust", in which case it is worth ACE_LOW_VALUE.
     */
    private int getHandValue()
    {
        handValue = 0;  // set the handValue back to 0
             
        // calculate hand value ignoring ACE_LOW_VALUE
        for ( Card eachCard : hand )
        {
            handValue += eachCard.getValue();
        }

        // if the hand value is > 21 check for aces
        if ( handValue > 21 )
        {
            handValue = 0; // reset handValue as we're recalculating
            
            for ( Card eachCard : hand )
            {
                if ( eachCard.getValue() != ACE_HIGH_VALUE )
                {
                    handValue += eachCard.getValue();
                }
                else
                {
                    handValue += ACE_LOW_VALUE;
                } // end inner if
            } // end for
        } // end if

        return handValue;
    }
    
    /**
     * Calculate total points
     */
    private void totalGamePoints()
    {
        if ( getHandValue() < 16 )
        {
            totalPoints += 0;   // award 0 points
        }
        else if ( getHandValue() < 21 && getHandValue() > 16 )
        {
            totalPoints += 1;   // award 1 point
        }
        else if ( getHandValue() == 21 )
        {
            totalPoints += 5;   // award 5 points
        }
    }
 
    /**
     * Shows the cards in the player's hand.
     */
    private void showHand()
    {
        System.out.println("\nYour cards:");
        for ( Card eachCard : hand )
        {
            System.out.println( " - " + eachCard.toString() );
        }
        
        // print out busted or blackjack depending on hand value
        if ( getHandValue() > 21 )
        {
            System.out.println("\n~~~~ Busted! ~~~~");
            totalGamePoints();  // calculate total game points
            notBustOrBlackJack = false;
        }
        else if ( getHandValue() == 21 )
        {
            System.out.println("\n**** BlackJack! ****");
            totalGamePoints();  // calculate total game points
            notBustOrBlackJack = false;
        }
        
        showTotals();         // show the totals
    }
    
    /**
     * Shows the current round, total points and hand value
     */
    private void showTotals()
    {      
        System.out.println("\nCurrent round: " + rounds + "\nTotal points: " + totalPoints
                           + "\nCurrent hand value: " + getHandValue() + "\n" );
    }
}