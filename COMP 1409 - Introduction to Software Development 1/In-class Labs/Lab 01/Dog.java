
/**
 * This is the Dog class! This class simply stores dog related variables and allows for output
 * and other random jibberish.
 * 
 * @author Steffen L. Norgren
 * @version April 17th, 2007
 */
public class Dog
{
    // Instance variables, which in this case are name, weight and neutered.
    private String name;
    private double weight;
    private boolean neutered;
    
    /**
     * Constructor for objects of class Dog (I'll refrain from comment)
     */
    public Dog( String dogName, double dogWeight )
    {
        // initialise instance variables
        name = dogName;
        weight = dogWeight;
        neutered = false;
    }
    
    /**
     * Returns the weight of the dog
     */
    public double getWeight()
    {
        // returns the weight
        return weight;
    }

    /**
     * Returns the name of the dog
     */
    public String getName()
    {
        // returns the weight
        return name;
    }
    
    /**
     * Returns the neutered status of the dog
     * Why don't you invoke getNeutered yourself!
     */
    public boolean getNeutered()
    {
        // returns the weight
        return neutered;
    }
    
    /**
     * Changes the dog's weight to a new value
     */
    public void setWeight( double newWeight )
    {
        weight = newWeight;
    }

    /**
     * Changes the dog's neuter status
     */
    public void neuter()
    {
        neutered = true;
    }
    /**
     * Prints something useless to the screen
     */
    public void eat()
    {
        System.out.println("yum");
    }

    /**
     * Prints something useless to the screen
     */
    public void run()
    {
        System.out.println("<pant>");
    }

    /**
     * Prints something useless to the screen
     */
    public void bark()
    {
        System.out.println("woof");
    }
    
    /**
     * Prints the dog's name
     */
    public void displayName()
    {
        System.out.println("Name: " + getName() );
    }
}
