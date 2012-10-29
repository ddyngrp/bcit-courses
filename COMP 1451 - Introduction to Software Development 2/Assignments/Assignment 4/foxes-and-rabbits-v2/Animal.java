import java.util.List;

/**
 * Animal is an abstract superclass for animals.
 * It provides features common to all animals,
 * such as the location and age.
 * 
 * @author David J. Barnes, Michael Kolling, and Steffen L. Norgren
 * @version 2007.08.14
 */
public abstract class Animal implements Actor
{
    // The animal's age.
    private int age;
    // Whether the animal is alive or not.
    private boolean alive;
    // The animal's position
    private Location location;

    /**
     * Create a new animal with age zero (a new born).
     */
    public Animal()
    {
        age = 0;
        alive = true;
    }
   
    /**
     * Check whether the actor is alive or not.
     * @return True if the actor is still alive.
     */
    public boolean isAlive()
    {
        return alive;
    }

    /**
     * Tell the actor that it's dead now :(
     */
    public void setDead()
    {
        alive = false;
    }
    
    /**
     * Return the actor's age.
     * @return The actor's age.
     */
    public int getAge()
    {
        return age;
    }

    /**
     * Set the actor's age.
     * @param age The actor's age.
     */
    public void setAge(int age)
    {
        this.age = age;
    }
    
    /**
     * Return the actor's location.
     * @return The actor's location.
     */
    public Location getLocation()
    {
        return location;
    }

    /**
     * Set the actor's location.
     * @param row The vertical coordinate of the location.
     * @param col The horizontal coordinate of the location.
     */
    public void setLocation(int row, int col)
    {
        this.location = new Location(row, col);
    }

    /**
     * Set the actor's location.
     * @param location The actor's location.
     */
    public void setLocation(Location location)
    {
        this.location = location;
    }
}
