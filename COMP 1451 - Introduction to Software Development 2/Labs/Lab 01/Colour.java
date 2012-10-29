
/**
 * Write a description of class Colour here.
 * 
 * @author Steffen L. Norgren 
 * @version July 11, 2007
 */
public class Colour
{
    private String colour;
    private int weight;
    
    /**
     * Default constructor
     */
    public Colour( String newColour, int newWeight )
    {
        colour = newColour;
        weight = newWeight;
    }
    
    public String toString()
    {
        return colour + " weight " + weight;
    }
}
