
/**
 * Write a description of class Cat here.
 * 
 * @author Steffen L. Norgren
 * @version May 30, 2007
 */

import java.util.ArrayList;

public class Cattery
{
    private ArrayList<Cat> catCollection;
    private String cattery;
    
    /**
     * Constructor for Cattery
     */
    public Cattery( String newCattery )
    {
        catCollection = new ArrayList<Cat>();
        cattery = newCattery;
    }
    
    /**
     * Adds new cat to the collection
     */
    public void storeCat( Cat newCat )
    {
        catCollection.add( newCat );
    }
    
    /**
     * Return the details of the cat at a particular position
     */
    public void displayStoredCat( int displayPosition )
    {
        if ( displayPosition > catCollection.size() )
        {
            System.out.println("There be dragons here!");
        }
        else if ( displayPosition < catCollection.size() && displayPosition >= 0  )
        {
            System.out.println( "Cat Name: " +
                                catCollection.get( displayPosition ).getCatName() );
            System.out.println( "Cat's Year of Birth: " +
                                catCollection.get( displayPosition ).getCatYearOfBirth() );
            System.out.println( "Cat's Weight in Pounds: " +
                                catCollection.get( displayPosition ).getCatWeightInPounds() );
        }
        else
        {
            System.out.println("There be serpents here!");
        }
    }
    
    /**
     * Delete the cat at a particular position
     */
    public void removeStoredCat( int deletePosition )
    {
        if ( deletePosition > catCollection.size() )
        {
            System.out.println("There be dragons here!");
        }
        else if ( deletePosition < catCollection.size() && deletePosition >= 0 )
        {
            catCollection.remove( deletePosition );
        }
        else
        {
            System.out.println("There be serpents here!");
        }
    }
    
    /**
     * Show all cat objects
     */
    public void displayAllStoredCats()
    {
        for ( Cat eachCat : catCollection )
        {
            System.out.println( eachCat.getCatName() );
        }
    }
}
