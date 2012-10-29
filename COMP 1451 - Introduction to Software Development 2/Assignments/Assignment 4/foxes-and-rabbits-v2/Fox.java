import java.util.List;
import java.util.Iterator;
import java.util.Random;

/**
 * A simple model of a fox.
 * Foxes age, move, eat rabbits, and die.
 * 
 * @author David J. Barnes, Michael Kolling, and Steffen L. Norgren
 * @version 2007.08.14
 */
public class Fox extends Animal implements Predator, Prey
{
    // Characteristics shared by all foxes (static fields).
    
    // The age at which a fox can start to breed.
    private static final int BREEDING_AGE = 2;
    // The age to which a fox can live.
    private static final int MAX_AGE = 10;
    // The likelihood of a fox breeding.
    private static final double BREEDING_PROBABILITY = 0.09;
    // The maximum number of births.
    private static final int MAX_LITTER_SIZE = 3;
    // The food value of a single rabbit. In effect, this is the
    // number of steps a fox can go before it has to eat again.
    private static final int RABBIT_FOOD_VALUE = 4;
    // A shared random number generator to control breeding.
    private static final Random rand = new Random();
    
    // Individual characteristics (instance fields).

    // The fox's food level, which is increased by eating rabbits.
    private int foodLevel;
    // The current step for this instance
    private int step = 0;
    
    /**
     * Create a fox. A fox can be created as a new born (age zero
     * and not hungry) or with random age.
     * @param randomAge If true, the fox will have random age and hunger level.
     */
    public Fox(boolean randomAge)
    {
        super();
        if(randomAge) {
            setAge(rand.nextInt(MAX_AGE));
            foodLevel = rand.nextInt(RABBIT_FOOD_VALUE);
        }
        else {
            // leave age at 0
            foodLevel = RABBIT_FOOD_VALUE;
        }
    }
    
    /**
     * This is what the fox does most of the time: it hunts for
     * rabbits. In the process, it might breed, die of hunger,
     * or die of old age.
     * @param currentField The field currently occupied.
     * @param updatedField The field to transfer to.
     * @param newAnimals A list to add newly born foxes to.
     */
    public void act(Field currentField, Field updatedField,
                    List<Actor> newActors, List<String> deathStats)
    {   
        // keep track of the current actor's age.
        step++;
        // increment the age every 100 steps
        if(step % 100 == 0) {
            if(incrementAge()) {
                deathStats.add("oldage");
            }
        }
        incrementHunger();
        if(isAlive()) {
            // New foxes are born into adjacent locations.
            int births = breed();
            for(int b = 0; b < births; b++) {
                Actor newFox = new Fox(false);
                newActors.add(newFox);
                Location newLocation = updatedField.freeAdjacentLocation(
                                                                     getLocation());
                // if the new fox cannot be placed in an adjacent location
                // it will simply cease to exist. Call it a stillbirth. ;-)
                if(newLocation != null) {
                    newFox.setLocation(newLocation);
                    updatedField.place(newFox);                    
                }
                else {
                    newActors.remove(newFox);
                    newFox.setDead();
                }
            }
            // Move towards the source of food if found.
            Location newLocation = findFood(currentField, getLocation());
            if(newLocation == null) {  // no food found - move randomly
                newLocation = updatedField.freeAdjacentLocation(getLocation());
            }
            if(newLocation != null) {
                setLocation(newLocation);
                updatedField.place(this);  // sets location
            }
            else {
                // can neither move nor stay - overcrowding - all locations taken
                setDead();
                deathStats.add("overcrowded");
            }
        }
    }
    
    /**
     * Increase the age. This could result in the fox's death.
     */
    private boolean incrementAge()
    {
        setAge(getAge() + 1);
        if(getAge() > MAX_AGE) {
            setDead();
            return true;
        }
        return false;
    }
    
    /**
     * Make this fox more hungry. This could result in the fox's death.
     */
    private void incrementHunger()
    {
        foodLevel--;
        if(foodLevel <= 0) {
            setDead();
        }
    }
    
    /**
     * Tell the fox to look for rabbits adjacent to its current location.
     * Only the first live rabbit is eaten.
     * @param field The field in which it must look.
     * @param location Where in the field it is located.
     * @return Where food was found, or null if it wasn't.
     */
    private Location findFood(Field field, Location location)
    {
        Iterator<Location> adjacentLocations =
                          field.adjacentLocations(location);
        while(adjacentLocations.hasNext()) {
            Location where = adjacentLocations.next();
            Actor actor = field.getActorAt(where);
            if(actor instanceof Prey && !(actor instanceof Predator)) {
                Actor rabbit = (Prey) actor;
                if(rabbit.isAlive()) { 
                    rabbit.setDead();
                    foodLevel = RABBIT_FOOD_VALUE;
                    return where;
                }
            }
        }
        return null;
    }
        
    /**
     * Generate a number representing the number of births,
     * if it can breed.
     * @return The number of births (may be zero).
     */
    private int breed()
    {
        int births = 0;
        if(canBreed() && rand.nextDouble() <= BREEDING_PROBABILITY) {
            births = rand.nextInt(MAX_LITTER_SIZE) + 1;
        }
        return births;
    }
    
    /**
     * @return A string representation of the fox.
     */
    public String toString()
    {
        return "Fox, age " + getAge();
    }

    /**
     * A fox can breed if it has reached the breeding age.
     */
    private boolean canBreed()
    {
        return getAge() >= BREEDING_AGE;
    }
}