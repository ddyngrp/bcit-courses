
/**
 * Card class. This is an individual card that could be used in 
 * any game. This class is complete and requires no changes.
 * 
 * @author Colleen Penrowley 
 * @version Fall 2005
 */
public class Card
{
    private String suit;            // card's suit, e.g. "Hearts" or "Clubs"
    private int value;              // card's face value
    private String description;     // card's description, e.g. "Two", "Ten", "King", "Queeen", "Ace"

    /**
     * Constructor for objects of class Card
     */
    public Card(String description, String suit, int value)
    {
        this.description = description;
        this.suit = suit;
        this.value = value;
    }

    /**
     * Gets the value of the card. Face cards are counted as 10.
     * @return     the card's value as an int
     */
    public int getValue()
    {
        return value;
    }
    
    /**
     * Gets the card's suit, e.g. "Hearts", "Diamonds"
     * @return the suit as a String
     */
    public String getSuit()
    {
        return suit;
    }
    
    /**
     * Gets the card's description, e.g. "ten", "king", "ace"
     * @return the card's description as a String
     */
    public String getDescription()
    {
        return description;
    }
    
    /**
     * returns the String representation of this Card.
     */
    public String toString()
    {
        return description + " of " + suit;
    }
}
