import java.util.Random;

/**
 * This class provides a grid (two-dimensional array) to be used as part of a 
 * game. Method stubs have been provided for you in this class, with comments 
 * that explain what each method will do. Part of your task is to design the 
 * logic and implement the methods. 
 * 
 * @author interface provided by Colleen Penrowley
 * @author Steffen L. Norgren
 * @version July 17, 2007
 */
public class Grid
{
    // suggested Grid constants
    public static final int ROWS = 5;      // number of rows in the grid
    public static final int COLUMNS = 5;   // number of columns in the grid
 
    // suggested Grid instance variables
    private char[][] grid;                  // the grid itself, a 2-D array of char
    private Random random;                  // random number generator

    /**
     * The Grid constructor creates a new grid using public constants ROWS and COLUMNS. 
     * Constructor also creates a new random number generator. The slots in the array
     * are initialized to char 0 (null char) by default.
     */
    public Grid()
    {
        grid = new char [ROWS][COLUMNS]; // create a 2-D array with ROWS rows and COLUMNS columns
        random = new Random();
    }
    
    /** 
     * Displays a grid on the terminal window. This method will be invoked on the display grid, and
     * on the working grid at the end of the game.
     */ 
    public void showGrid()
    {
        // nested for loop to display the grid
        for ( int row = 0; row < getNumRows(); row++ )
        {
            for ( int column = 0; column < getNumColumns(); column++ )
            {
                // format the output so each line is as long as the number of columns
                if ( column == getNumColumns() -1 )
                {
                    // create a new line after the data
                    System.out.println( grid[row][column] );
                }
                else
                {
                    // add a space after each
                    System.out.print( grid[row][column] + " " );
                }
            }
        }

        System.out.println(); // pad one line after the grid
    }
    
    /** 
     * Generates random coordinates, puts them into a new CoordinatePair,
     * returns CoordinatePair - This method is complete and requires no change.
     * @return a randomly-generated pair of coordinates within the bounds of the
     * grid
     */
    private CoordinatePair getRandomCoordinates()
    {
        CoordinatePair coords = new CoordinatePair();  // create a new coordinate pair object
        coords.setRow(random.nextInt(ROWS));           // randomly select a row, put row info into object
        coords.setColumn(random.nextInt(COLUMNS));     // randomly select a column, put column info into object
        return coords;                                 // return the object
    }
    
    /**
     * Invokes getRandomCoordinates() to put a specific value into the number of
     * grid positions specified by the first parameter, e.g. 
     * setRandomCoordinates(5, 'T') will set the target char 'T' into 5 different
     * locations in the grid on which it is invoked. This method will be invoked on the 
     * working grid.
     * @param the number of randomly-generated coordinates to set with the value,
     * the target value to set
     */
    public void setRandomCoordinates(int numCoordsToSet, char valueToSet)
    {
        int currentRow = getRandomCoordinates().getRow();        // temporary variable for the random return
        int currentColumn = getRandomCoordinates().getColumn();  // temporary variable for the random return
        
        // uses a loop to set numCoordsToSet DIFFERENT locations with valueToSet
        for ( int i = 0; i < numCoordsToSet; i++ )
        {
            // if the spot is taken, generate new random rows and columns
            while ( grid[currentRow][currentColumn] != '\0' )
            {
                currentRow = getRandomCoordinates().getRow();
                currentColumn = getRandomCoordinates().getColumn();
            }
            
            grid[currentRow][currentColumn] = valueToSet;
        }
    }
    
    /**
     * Sets the specified value in a grid at the location specified by the CoordinatePair parameter. 
     * This method will be invoked on the display grid.
     * @param CoordinatePair object containing the coordinates, and the value to put into that
     * location as a char. This value will indicate "hit" or "miss".
     */
    public void setSpecificCoordinates(CoordinatePair coordsToSet, char valueToSet)
    {
        grid[coordsToSet.getRow()][coordsToSet.getColumn()] = valueToSet;
    }
    
    /**
     * Gets the contents of a grid at the specified row column location.
     * @return the grid contents as a char
     */
    public char getContents(int row, int column)
    {
        // a little bit of error checking
        if ( row < getNumRows() && column < getNumColumns() )
        {
            return grid[row][column]; // return contents
        }
        else
        {
            return '?'; // returns a ? to signify there was an error
        }
    }
    
    /**
     * Gets the number of rows in the grid.
     * @return the number of rows as an int.
     */
    public int getNumRows()
    {
        return grid.length;
    }
     
    /**
     * Gets the number of columns in the grid.
     * @return the number of columns as an int.
     */
    public int getNumColumns()
    {
        return grid[0].length;
    }
    
    
}
