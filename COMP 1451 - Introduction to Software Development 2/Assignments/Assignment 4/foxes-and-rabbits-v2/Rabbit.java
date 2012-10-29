import java.util.List;
import java.util.Random;

/**
 * A simple model of a rabbit.
 * Rabbits age, move, breed, and die.
 * 
 * @author David J. Barnes, Michael Kolling, and Steffen L. Norgren
 * @version 2007.08.14
 */
public class Rabbit extends Animal implements Prey
{
    // Characteristics shared by all rabbits (static fields).

    // The age at which a rabbit can start to breed.
    private static final int BREEDING_AGE = 2;
    // The age to which a rabbit can live.
    private static final int MAX_AGE = 4;
    // The likelihood of a rabbit breeding.
    private static final double BREEDING_PROBABILITY = 0.15;
    // The maximum number of births.
    private static final int MAX_LITTER_SIZE = 5;
    // A shared random number generator to control breeding.
    private static final Random rand = new Random();
    
    // Individual characteristics (instance fields).
    
    // The current step for this instance
    private int step = 0;
    
    /**
     * Create a new rabbit. A rabbit may be created with age
     * zero (a new born) or with a random age.
     * 
     * @param randomAge If true, the rabbit will have a random age.
     */
    public Rabbit(boolean randomAge)
    {
        super();
        if(randomAge) {
            setAge(rand.nextInt(MAX_AGE));
        }
    }
    
    /**
     * This is what the rabbit does most of the time - it runs 
     * around. Sometimes it will breed or die of old age.
     * @param currentField The field currently occupied.
     * @param updatedField The field to transfer to.
     * @param newActors A list to add newly born rabbits to.
     */
    public void act(Field currentField, Field updatedField,
                    List<Actor> newActors, List<String> deathStats)
    {
        // keep track of the current actor's age.
        step++;
        // increment the age every 100 steps
        if(step % 100 == 0) {
            incrementAge();
        }
        if(isAlive()) {
            int births = breed();
            for(int b = 0; b < births; b++) {
                Actor newRabbit = new Rabbit(false);
                newActors.add(newRabbit);
                
                Location newLocation = updatedField.freeAdjacentLocation(
                                                                     getLocation());
                // if the new rabbit cannot be placed in an adjacent location
                // it will simply cease to exist. Call it a stillbirth. ;-)
                if(newLocation != null) {
                    newRabbit.setLocation(newLocation);
                    updatedField.place(newRabbit);                    
                }
                else {
                    // can neither move nor stay - overcrowding - all locations taken
                    newActors.remove(newRabbit);
                    newRabbit.setDead();
                }
            }
            Location newLocation = updatedField.freeAdjacentLocation(getLocation());
            // Only transfer to the updated field if there was a free location
            if(newLocation != null) {
                setLocation(newLocation);
                updatedField.place(this);
            }
            else {
                // can neither move nor stay - overcrowding - all locations taken
                setDead();
            }

        }
    }
    
    /**
     * Increase the age.
     * This could result in the rabbit's death.
     */
    private void incrementAge()
    {
        setAge(getAge() + 1);
        if(getAge() > MAX_AGE) {
            setDead();
        }
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
     * @return A string representation of the rabbit.
     */
    public String toString()
    {
        return "Rabbit, age " + getAge();
    }

    /**
     * A rabbit can breed if it has reached the breeding age.
     */
    private boolean canBreed()
    {
        return getAge() >= BREEDING_AGE;
    }
}
