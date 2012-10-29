import java.util.List;
import java.util.Iterator;
import java.util.Random;

/**
 * A simple model of a trapper.
 * Trappers age, move, trap foxes, give up (not successful at trapping),
 * and retire.
 * 
 * @author David J. Barnes, Michael Kolling, and Steffen L. Norgren
 * @version 2007.08.14
 */
public class Trapper extends Animal implements Predator
{
    // Characteristics shared by all trapperes (static fields).
    
    // The minimum age at which a one can become a trapper.
    private static final int MIN_AGE = 16;
    // The age to which a trapper can live.
    private static final int MAX_AGE = 75;
    // A shared random number generator to control breeding.
    private static final Random rand = new Random();
    
    // Individual characteristics (instance fields).

    // The number of foxes the trapper has trapped.
    private int trappedFoxes = 0;
    // The minimum number of foxes that can be trapped.
    private int minFoxesTrapped;
    // The maximum number of foxes that can be trapped.
    private int maxFoxesTrapped;
    // The current step for this instance
    private int step = 0;

    /**
     * Create a trapper. A trapper can be created at a random age or
     * at the minimum age.
     * @param randomAge If true, the trapper will have random.
     * @param minFoxesTrapped the minimum number of foxes a trapper can trap
     * @param maxFoxesTrapped the maximum number of foxes a trapper can trap
     */
    public Trapper(boolean randomAge, int minFoxesTrapped, int maxFoxesTrapped)
    {
        super();
        if(randomAge) {
            setAge(rand.nextInt(MAX_AGE - MIN_AGE) + MIN_AGE);
        }
        else
        {
            setAge(MIN_AGE);
        }
        this.minFoxesTrapped = minFoxesTrapped;
        this.maxFoxesTrapped = maxFoxesTrapped;
    }
    
    /**
     * This is what the trapper does most of the time: it hunts for
     * rabbits. In the process, it might breed, die of hunger,
     * or die of old age.
     * @param currentField The field currently occupied.
     * @param updatedField The field to transfer to.
     * @param newActors A list to add new trapperes to.
     */
    public void act(Field currentField, Field updatedField,
                    List<Actor> newActors, List<String> deathStats)
    {
        // keep track of the current actor's age.
        step++;
        // increment the age every 100 steps
        if(step % 100 == 0) {
            incrementAge();
            if(trappedFoxes < minFoxesTrapped) {
                setDead();
                deathStats.add("futile");
            }
            else {
                trappedFoxes = 0;
            }
        }
        if(isAlive()) {
            // if the trapper's limit hasn't been reached, by all means, look for more!
            if(trappedFoxes < maxFoxesTrapped) {
                // Move towards the last successful trapped fox location
                Location newLocation = findFox(currentField, getLocation(), deathStats);
                if(newLocation == null) {  // no foxes trapped - move randomly
                    newLocation = updatedField.freeAdjacentLocation(getLocation());
                }
                if(newLocation != null) {
                    setLocation(newLocation);
                    updatedField.place(this);  // sets location
                }
            }
            // the trapper has no inclination to move towards foxes as he
            // has reached his limit for the year.
            else {
                setLocation(getLocation());
                updatedField.place(this);
            }
        }
        else {
            if(getAge() > MAX_AGE)
            {
                deathStats.add("retired");
            }
            Actor newTrapper = new Trapper(true, minFoxesTrapped, maxFoxesTrapped);
            newActors.add(newTrapper);
                
            Location newLocation = updatedField.randomAdjacentLocation(getLocation());
            // new trappers simply squish whatever happens to be nearby.
            if(newLocation != null) {
                newTrapper.setLocation(newLocation);
                updatedField.place(newTrapper);    
            }
        }
    }
    
    /**
     * Increase the age. This could result in the trapper's retirement.
     */
    private void incrementAge()
    {
        setAge(getAge() + 1);
        if(getAge() > MAX_AGE) {
            setDead();
        }
    }
    
    /**
     * Tell the trapper to look for foxes adjacent to its current location.
     * All foxes in adjacent locations will be trapped.
     * @param field The field in which it must look.
     * @param location Where in the field it is located.
     * @return location of the last successful trap.
     */
    private Location findFox(Field field, Location location, List<String> deathStats)
    {
        Iterator<Location> adjacentLocations = field.adjacentLocations(location);
        while(adjacentLocations.hasNext()) {
            Location where = adjacentLocations.next();
            Actor actor = field.getActorAt(where);
            if(actor instanceof Predator && actor instanceof Prey) {
                Actor fox = (Prey) actor;
                // check to see if the trapper has reached his limit
                if(getTrappedFoxes() < maxFoxesTrapped) {
                    if(fox.isAlive()) { 
                        fox.setDead();
                        trappedFoxes += 1;
                        deathStats.add("trapped");
                    }
                }
                return where;
            }
        }
        return null;
    }
    
    /**
     * @return the number of foxes that the trapper has trapped.
     */
    private int getTrappedFoxes()
    {
        return trappedFoxes;
    }
    
    /**
     * @return A string representation of the trapper.
     */
    public String toString()
    {
        return "Trapper, age " + getAge();
    }
}