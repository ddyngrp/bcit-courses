
/**
 * Write a description of class Bat here.
 * 
 * @author Steffen L. Norgren
 * @version 2007.08.17
 */
public class Bat extends Animal implements Mammal
{
    private static final String specialMove =
                                "I fly at night.";
    private String furColour;

    /**
     * Constructor for bat
     */
    public Bat(String species, int age, double weightKG, String furColour)
    {
        super(species, age, weightKG);
        this.furColour = furColour;
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
    public String getFurColour()
    {
        return furColour;
    }
    
    /**
     * toString method for Mammel objects
     */
    public String toString()
    {
        String returnString;
        
        returnString = super.toString();
        returnString += "Fur colour: " + getFurColour() + "\n";
        returnString += getMove() + "\n";

        return returnString;
    }
}
