import java.util.Random;
import java.util.Arrays;

/**
 * Write a description of class Grid here.
 * 
 * @author Steffen L. Norgren 
 * @version July 11, 2007
 */
public class Grid
{
    private Colour[][] colour;
    
    public Grid( int gridRows, int gridColumns )
    {
        colour = new Colour[gridRows][gridColumns];
    }
    
    /**
     * Returns the number of rows in the grid, length of the grid
     */
    private int getRows()
    {
        return colour.length;
    }
    
    /**
     * Returns the number of columns in the grid, length of a row
     */
    private int getColumns()
    {
        return colour[0].length;
    }
    
    /**
     * Loads half the grid at randomly-chossen locations (half if total
     * locations is even, otherwie half-1). Each choen location will get
     * a new Colour object reference with colour and weight randomly
     * chosen. Do not replace one Colour object with another.
     * Possible colours are: red, blue, green, yellow, orange.
     * Possible weights are between 1 and 6 inclusive.
     */
    public void loadGrid()
    {
        Random rand = new Random();
        int halfGrid = (getRows() * getColumns()) / 2;
        int currentColumn;
        int currentRow;
        
        for ( int grid = 0; grid < halfGrid; grid++ )
        {
            currentColumn = rand.nextInt( getColumns() );
            currentRow = rand.nextInt( getRows() );
            
            while ( colour[currentRow][currentColumn] != null )
            {
                currentColumn = rand.nextInt( getColumns() );
                currentRow = rand.nextInt( getRows() );
            }
            
            colour[currentRow][currentColumn] = new Colour( randomColour(), rand.nextInt(5) + 1 );
        }
    }
    
    /**
     * Return a random Colour
     */
    private String randomColour()
    {
        Random rand = new Random();
        String colour;
        
        switch ( rand.nextInt(5) )
        {
            case 0:
                colour = "red";
                break;
            case 1:
                colour = "blue";
                break;
            case 2:
                colour = "green";
                break;
            case 3:
                colour = "yellow";
                break;
            case 4:          
                colour = "orange";
                break;
            default:
                colour = "PROBLEM!";
                break;
        }
        
        return colour;
    }
    
    /**
     * Displays the grid contentsss, e.g. for a 3x3 grid:
     * yellow weight 1 at location 1,0
     * red weight 6 at location 1,1
     * ...
     */
    public void diplayGrid()
    {
        for ( int row = 0; row < getRows(); row++ )
        {
            for ( int column = 0; column < getColumns(); column++ )
            {
                if ( colour[row][column] != null )
                {
                    System.out.println( colour[row][column] + " at location " + row + "," + column );
                }
            }
        }
    }
}
