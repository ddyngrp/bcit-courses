
/**
 * Write a description of class Cat here.
 * 
 * @author Steffen L. Norgren
 * @version May 30, 2007
 */
public class Cat
{
    private String catName;
    private int catYearOfBirth;
    private double catWeightInPounds;
    
    /**
     * Constructor for class Cat
     */
    public Cat( String newCatName, int newCatYearOfBirth,
                double newCatWeightInPounds )
    {
        catName = newCatName;
        catYearOfBirth = newCatYearOfBirth;
        catWeightInPounds = newCatWeightInPounds;
    }
    
    /**
     * Getter for catName
     */
    public String getCatName()
    {
        return catName;
    }
    
    /**
     * Getter for catYearOfBirth
     */
    public int getCatYearOfBirth()
    {
        return catYearOfBirth;
    }
    
    /**
     * Getter for catWeightInPounds
     */
    public double getCatWeightInPounds()
    {
        return catWeightInPounds;
    }
}
