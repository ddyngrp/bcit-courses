import java.util.Random;
import java.util.Arrays;

/**
 * Write a description of class Grid here.
 * 
 * @author Steffen L. Norgren 
 * @version June 19, 2007
 */
public class Grid
{
    private GridPoint gridPoint; 
    private static final int MAX_VALUE = 99;
    private int[][] twoDeeArray;
    
    public Grid( int gridRows, int gridColumns )
    {
        twoDeeArray = new int[gridRows][gridColumns];
    }
    
    /**
     * Returns the number of rows in the grid
     */
    public int getRows()
    {
        return twoDeeArray.length;
    }
    
    /**
     * Returns the number of columns in the grid
     */
    public int getColumns()
    {
        return twoDeeArray[0].length;
    }
    
    /**
     * Loads the grid with random values between 0 and MAX_VALUE.
     */
    public void loadGrid()
    {
        Random rand = new Random(); // Default seed comes from system time
        
        for ( int row = 0; row < getRows(); row++ )
        {
            for ( int column = 0; column < getColumns(); column++ )
            {
                twoDeeArray[row][column] = rand.nextInt( MAX_VALUE );
            }
        }
    }
    
    /**
     * Displays the grid contents in table format.
     */
    public void displayGrid()
    {
        String spacer = "   ";
        
        for ( int row = 0; row < getRows(); row++ )
        {
            for ( int column = 0; column < getColumns(); column++ )
            {
                if ( twoDeeArray[row][column] < 10 )
                {
                    spacer = "   ";
                }
                else if ( twoDeeArray[row][column] >= 10 && twoDeeArray[row][column] < 100 )
                {
                    spacer = "  ";
                }
                else if ( twoDeeArray[row][column] >= 100 && twoDeeArray[row][column] < 1000 )
                {
                    spacer = " ";
                }
                System.out.print( twoDeeArray[row][column] + spacer );
            }
            System.out.println();
        }
    }
    
    /**
     * Searches the grid for the specified value and returns the coordinates
     * as a GridPoint object or returns null if not found. If there are
     * duplicates, only the first instance will be found.
     */
    public GridPoint getCoordinates( int valueSought )
    {
        for ( int row = 0; row < getRows(); row++ )
        {
            for ( int column = 0; column < getColumns(); column++ )
            {
                if ( twoDeeArray[row][column] == valueSought )
                {
                    return new GridPoint( row, column );
                }
            }
        }
        
        return null; // if nothing is found
    }
}