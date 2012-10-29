
/**
 * Write a description of class Hummingbird here.
 * 
 * @author Steffen L. Norgren
 * @version 2007.08.17
 */
public class Hummingbird extends Animal implements Bird
{
    private static final String specialMove =
                                "I flit from flower to flower.";
    private String eggColour;
    private double flightSpeedKMH;

    /**
     * Constructor for hummingbird
     */
    public Hummingbird(String species, int age, double weightKG,
                       String eggColour, double flightSpeedKMH)
    {
        super(species, age, weightKG);
        this.eggColour = eggColour;
        this.flightSpeedKMH = flightSpeedKMH;
    }
    
    /**
     * Get this animal's special move
     * @return String of the animal's move
     */
    public String getMove()
    {
        return specialMove;
    }
    
    /**
     * Getter for this animal's fur colour.
     * @return String representing the colour of the fur.
     */
    public String getEggColour()
    {
        return eggColour;
    }
    
    /**
     * Getter for this animal's flight speed.
     * @return double representing the animal's flight speed in km/hr.
     */
    public double getFlightSpeedKMH()
    {
        return flightSpeedKMH;
    }
    
    /**
     * toString method for Bird objects
     */
    public String toString()
    {
        String returnString;
        
        returnString = super.toString();
        returnString += "Egg colour: " + getEggColour() + "\n";
        returnString += "Flight speed in km/hr: " + getFlightSpeedKMH() + "\n";
        returnString += getMove() + "\n";

        return returnString;
    }
}
