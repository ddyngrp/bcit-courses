
/**
 * Write a description of class Game here.
 * 
 * @author Steffen L. Norgren
 * @version July 17, 2007
 */
public class Game
{
    // suggested Game constants
    public static final char TARGET = 'T';          // the char used to indicate a target
    public static final char HIT = '*';             // the char used to indicate a hit
    public static final char MISS = '-';            // the char used to indicate a miss
    public static final int NUMBER_OF_TARGETS = 10; // number of targets hidden in the game grid
    public static final int NUMBER_OF_TRIES   = 10; // number of tries the user is given
    
    // suggested instance variables
    private Grid workingGrid;                       // the grid that holds the targets
    private Grid displayGrid;                       // the grid that displays hits and misses
    private InputReader reader;                     // input reader to get user coordinate choices

    /**
     * Constructor for objects of class Game
     */
    public Game()
    {
        workingGrid = new Grid();   // create two new grids
        displayGrid = new Grid();
        workingGrid.setRandomCoordinates(NUMBER_OF_TARGETS, TARGET);    // set targets
        reader = new InputReader(); // get an input reader
        
        playGame();                 // automatically start the game
    }
    /**
     * Play the game - this method contains the game logic
     */
    public void playGame()
    {
        int tries = 0;              // initialize current try to 0
        
        showInstructions();         // show the instructions to the user
        
        // continue playing until the limit of tries has been reached
        while ( tries < NUMBER_OF_TRIES )
        {
            displayGrid.showGrid();     // display the grid
            CoordinatePair input = reader.getCoordinates();   // get user input
            
            // verify the user input
            while ( checkGrid( input ) == false )
            {
                input = reader.getCoordinates();   // get user input
            }
            
            // sets the location specified on the displayGrid to a hit or miss
            // depending on the return value of checkHitMiss()
            displayGrid.setSpecificCoordinates( input, checkHitMiss( input ) );

            tries++;
        }
        
        displayGrid.showGrid();     // display the final grid
        
        // show the number of hits and display an appropriate message
        if ( getHits() < NUMBER_OF_TARGETS )
        {
            System.out.println("Sorry, you only hit " + getHits() + " targets out of " + NUMBER_OF_TARGETS + ".\n" +
                               "Prepare for the long and painful death of you and your species." );
        }
        else
        {
            System.out.println("Holy cow! You got all " + getHits() + " targets out of " + NUMBER_OF_TARGETS + "!\n" +
                               "Zarquon will now disect your brain to discover how you managed this feat!" );
        }
        
        workingGrid.showGrid(); // show the locations of the targets
    }
    
    /**
     * Returns the number of hits.
     * 
     * @return An int value representing the number of hits.
     */
    private int getHits()
    {
        int hits = 0;
        
        for ( int row = 0; row < displayGrid.getNumRows(); row++ )
        {
            for ( int column = 0; column < displayGrid.getNumColumns(); column++ )
            {
                // increments for each hit found
                if ( displayGrid.getContents( row, column ) == '*' )
                {
                    hits++;
                }
            }
        }
        
        return hits;
    }
    
    /**
     * Checks to see whether the user's input location represents a hit
     * or a miss and returns the value accordingly.
     * 
     * @param coordinates A CoordinatePair object representing the values chosen
     * @return A char value representing a hit or a miss.
     */
    private char checkHitMiss( CoordinatePair coordinates )
    {
        if ( workingGrid.getContents( coordinates.getRow(), coordinates.getColumn() ) == TARGET )
        {
            return HIT;
        }
        else
        {
            return MISS;
        }
    }
    
    /**
     * Checks whether the input coordinates are valid and returns
     * true or false depending on validity.
     * 
     * @param coordinates A CoordinatePair object representing the values chosen
     * @return A boolean value representing whether the input was valid
     */
    private boolean checkGrid( CoordinatePair coordinates )
    {
        // check for negative values
        if ( coordinates.getRow() < 0 || coordinates.getColumn() < 0 )
        {
            System.out.println("I'm sorry, you cannot print negative values. Please try again.");
            return false;
        }
        // check for values outside the grid area
        else if ( coordinates.getRow() >= displayGrid.getNumRows() || 
                  coordinates.getColumn() >= displayGrid.getNumColumns() )
        {
            System.out.println("I'm sorry, your entry was outside the limits of the game grid. Please try again.");
            return false;
        }
        else
        {
            // check to see if the user already tried that location
            if ( displayGrid.getContents( coordinates.getRow(), coordinates.getColumn() ) != '\0' )
            {
                System.out.println("I'm sorry, you already tried that location. Please try again.");
                return false;
            }
            
            // nothing to see here, carry on
            return true;
        }
    }
    
    /**
     * Provides instructions to the user
     */
    public void showInstructions()
    {
        System.out.println("Hello and welcome to the Guessing Game! Glory awaits you as you battle against\n" +
                          "the evil computer, Zarquon! Should you fail in your mission to guess all the\n" +
                          "correct locations, you and all your kind will be subjected to death by snoo-snoo.\n\n" +
                          "To play this diabolical game of wit, you must carefully select two locations in a\n" +
                          displayGrid.getNumRows() + " by " + displayGrid.getNumColumns() + " grid. But remember, " +
                          "the row and column numbers start with ZERO. As such,\n" +
                          "the convention for inputting your carefully strategized decisions is to input a\n" +
                          "number from 0 to " + (displayGrid.getNumRows() - 1) + " for the row followed by a space and" +
                          "then a number from 0 to " + (displayGrid.getNumColumns() -1) + "\nfor the column. e.g. \"0 3\" for " +
                          "a selection of row 0 and column 3 (without the quotes).\n\n" +
                          "Your goal is to discover through a careful analysis of random number algorithms,\n" +
                          "where the evil computer Zarquon has placed the " + NUMBER_OF_TARGETS + " targets within the game grid.\n" +
                          "You will be given no more than " + NUMBER_OF_TRIES + " to choose correctly. Failure is death!\n\n" +
                          "If you fail to understand these concepts, you might as well give up now.\nLet the game begin!\n" );
    }
}
