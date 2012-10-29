
/**
 * Write a description of class Stove here.
 * 
 * @author Steffen L. Norgren 
 * @version 07.25.2007
 */
public class Stove extends Appliances
{
    private int heatingElements;

    /**
     * Constructor for objects of class Stove
     */
    public Stove(String theMaker, int theSerialNumber,
                        double theHeightCM, double theDepthCM,
                        double theWidthCM,
                        int theHeatingElements)
    {
        super(theMaker, theSerialNumber, theHeightCM, theDepthCM, theWidthCM);
        heatingElements = theHeatingElements;
    }
    
    /**
     * Setter for heatingElements
     */
    public void setHeatingElements(int newHeatingElements)
    {
        heatingElements = newHeatingElements;
    }
    
    /**
     * Getter for heatingElements
     */
    public int getHeatingElements()
    {
        return heatingElements;
    }
}
