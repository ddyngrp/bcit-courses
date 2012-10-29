
/**
 * Write a description of class Refrigerator here.
 * 
 * @author Steffen L. Norgren 
 * @version 07.25.2007
 */
public class Refrigerator extends Appliances
{
    private double capacityM2;
    private double minTempC;

    /**
     * Constructor for objects of class Refrigerator
     */
    public Refrigerator(String theMaker, int theSerialNumber,
                        double theHeightCM, double theDepthCM,
                        double theWidthCM,
                        double theCapacityM2, double theMinTempC)
    {
        super(theMaker, theSerialNumber, theHeightCM, theDepthCM, theWidthCM);
        capacityM2 = theCapacityM2;
        minTempC = theMinTempC;
    }
    
    /**
     * Setter for capacityM2
     */
    public void setCapacityM2(double newCapacityM2)
    {
        capacityM2 = newCapacityM2;
    }
    
    /**
     * Setter for minTempC
     */
    public void setMinTempC(double newMinTempC)
    {
        minTempC = newMinTempC;
    }
    
    /**
     * Getter for capacityM2
     */
    public double getCapacityM2()
    {
        return capacityM2;
    }
    
    /**
     * Getter for minTempC
     */
    public double getMinTempC()
    {
        return minTempC;
    }
}
