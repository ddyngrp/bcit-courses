
/**
 * Write a description of class Appliances here.
 * 
 * @author Steffen L. Norgren 
 * @version 07.25.2007
 */
public class Appliances
{
    private String maker;
    private int serialNumber;
    private double heightCM;
    private double depthCM;
    private double widthCM;
    
    /**
     * Initialize the fields of the Appliance
     */
    public Appliances(String theMaker, int theSerialNumber,
                      double theHeightCM, double theDepthCM,
                      double theWidthCM)
    {
        maker = theMaker;
        serialNumber = theSerialNumber;
        heightCM = theHeightCM;
        depthCM = theDepthCM;
        widthCM = theWidthCM;
    }
    
    /**
     * Setter for maker
     */
    public void setMaker(String newMaker)
    {
        maker = newMaker;
    }
    
    /**
     * Setter for serialNumber
     */
    public void setSerialNumber(int newSerialNumber)
    {
        serialNumber = newSerialNumber;
    }
    
    /**
     * Setter for heightCM
     */
    public void setHeightCM(double newHeightCM)
    {
        heightCM = newHeightCM;
    }
    
    /**
     * Setter for depthCM
     */
    public void setDepthCM(double newDepthCM)
    {
        depthCM = newDepthCM;
    }
    
    /**
     * Setter for widthCM
     */
    public void setWidthCM(double newWidthCM)
    {
        widthCM = newWidthCM;
    }
    
    /**
     * Getter for maker
     */
    public String getMaker()
    {
        return maker;
    }
    
    /**
     * Getter for serialNumber
     */
    public int getSerialNumber()
    {
        return serialNumber;
    }
    
    /**
     * Getter for heightCM
     */
    public double getHeightCM()
    {
        return heightCM;
    }
    
    /**
     * Getter for depthCM
     */
    public double getDepthCM()
    {
        return depthCM;
    }
    
    /**
     * Getter for widthCM
     */
    public double getWidthCM()
    {
        return widthCM;
    }
}
