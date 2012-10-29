
/**
 * This class does things with array like things!
 * 
 * @author Steffen L. Norgren
 * @version June 12, 2007
 */

import java.util.Arrays;

public class ArrayWork
{
    private int[] intArray;    

    /**
     * Oh look! The default constructor
     */
    public ArrayWork()
    {
        intArray = new int[10];
    }
    
    /**
     * Oh look! An overloaded constructor
     */
    public ArrayWork( int arraySize )
    {
        intArray = new int[arraySize];
    }
    
    /**
     * Takes an int parameter and sets each element in the array
     * to the value of the parameter plus the value of the array index.
     */
    public void loadArray( int setArrayValues )
    {
        for ( int index = 0; index < intArray.length; index++ )
        {
            intArray[index] = index + setArrayValues;
        }
    }
    
    /**
     * This method iterates over the array and displays the index
     * positions of the array and the contents of each position
     */
    public void displayContents()
    {
        for ( int index = 0; index < intArray.length; index++ )
        {
            System.out.println( "index: " + index + " contains: " + intArray[index] );
        }
    }
    
    /**
     * This method iterates over the array and adds up the values
     * in the array then returns the sum.
     */
    public int reportSum()
    {
        int arraySummedValues = 0;
        
        for ( int index = 0; index < intArray.length; index++ )
        {
            arraySummedValues += intArray[index];
        }
        
        return arraySummedValues;
    }
    
    /**
     * This method takes an int parameter and returns TRUE if
     * the parameter value is in the array and false if not.
     */
    public boolean search( int findInArray )
    {
        for ( int index = 0; index < intArray.length; index++ )
        {
            if ( intArray[index] == findInArray )
            {
                return true;
            }
        }
        
        return false;
    }
}
