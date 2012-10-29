
/**
 * Abstract class Animal - write a description of the class here
 * 
 * @author Steffen L. Norgren
 * @version 2007.08.17
 */
public abstract class Animal
{
    private String species;
    private int age;
    private double weightKG;
    
    /**
     * Constructor for animal objects.
     * @param species the name of the animal's species
     * @param age the age of the animal
     * @param weightKG the weight of the animal in kilograms
     */
    public Animal(String species, int age, double weightKG)
    {
        this.species = species;
        this.age = age;
        this.weightKG = weightKG;
    }
    
    /**
     * Getter for animal's species
     * @return a string representing animal's species name.
     */
    public String getSpecies()
    {
        return species;
    }

    /**
     * Getter for animal's age
     * @return an int representing the age of the animal.
     */
    public int getAge()
    {
        return age;
    }

    /**
     * Getter for species
     * @return a double representing the weight of the animal in kilograms.
     */
    public double getWeightKG()
    {
        return weightKG;
    }
    
    /**
     * toString method for animal objects
     */
    public String toString()
    {
        String returnString;
        
        returnString = "Species: " + getSpecies() + "\n";
        returnString += "Age: " + getAge() + "\n";
        returnString += "Weight in kilos: " + getWeightKG() + "\n";
        
        return returnString;
    }
    
    public abstract String getMove();
}
