import java.util.List;

/**
 * The interface to be implemented by any class wishing
 * to participate in the simulation.
 * 
 * @author Steffen L. Norgren
 * @version 2007.08.14
 */

public interface Actor
{
    /**
     * Make this animal act - that is: make it do whatever
     * it wants/needs to do.
     * @param currentField The field currently occupied.
     * @param updatedField The field to transfer to.
     * @param newAnimals A list to add newly born animals to.
    */
    abstract public void act(Field currentField, Field updatedField,
                             List<Actor> newAnimals, List<String> deathStats);
                             
    abstract public boolean isAlive();
    
    abstract public Location getLocation();
    
    abstract public void setLocation(int row, int col);
    
    abstract public void setLocation(Location location);
    
    abstract public void setDead();
}
