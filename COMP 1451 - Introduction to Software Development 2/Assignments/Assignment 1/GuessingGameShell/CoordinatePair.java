
/**
 * Class CoordinatePair. This class maintains a row-column pair of numbers
 * to be used as array coordinates. A CoordinatePair object refers to a single
 * location in a two-dimensional array.
 * 
 * @author Colleen Penrowley 
 * @version August 2005
 */
public class CoordinatePair
{
	private int row;
	private int column;

	/**
	 * Constructor for objects of class CoordinatePair
	 */
	public CoordinatePair()
	{
		// initialise instance variables
		row = 0;
		column = 0;
	}

	/**
	 * Row accessor 
	 * @return   current row as int
	 */
	public int getRow()
	{
		return row;
	}
	
	/**
	 * Column accessor
	 * @return current column as int
	 */
	public int getColumn()
	{
	    return column;
	}
	
	/**
	 * Row mutator - sets row to the input value
	 * @param row as int
	 */
	public void setRow(int row)
	{
	    this.row = row;
	}
	
	/**
	 * Column mutator - sets column to the input value
	 * @param column as int
	 */
	public void setColumn(int column)
	{
	    this.column = column;
	}
}
