import java.util.ArrayList;
//import java.util.Iterator;

/**
 * Write a description of class ColleensYard here.
 * 
 * @author Steffen L. Norgren
 * @version 2007.08.17
 */
public class ColleensYard
{
    private ArrayList<Animal> animals;
    
    /**
     * Constructor for ColleensYard
     */
    public ColleensYard()
    {
        animals = new ArrayList<Animal>();
    }
    
    /**
     * New animal in colleen's yard
     */
    public void addAnimal(Animal animal)
    {
        animals.add(animal);
    }
    
    /**
     * Show information about all the animals in
     * Colleen's yard.
     */
    public void showAll()
    {
        for(Animal animal : animals) {
            System.out.println(animal);
        }
    }
    
    /**
     * Show information about the moves each animal
     * in Colleen's yard can do.
     */
    public void showMoves()
    {
        for(Animal animal : animals) {
            System.out.println(animal.getMove());
        }
    }
    
    /**
     * Calculates the average flight speed of all
     * the birds in the yard.
     * @return double the average flight speed of all birds,
     * returns null if there are no birds in the yard at all.
     */
    public double averageFlightSpeed()
    {
        double averageFlightSpeed = 0;
        int birdCount = 0;
        
        for(Animal animal : animals) {
            if(animal instanceof Bird) {
                averageFlightSpeed += ((Bird)animal).getFlightSpeedKMH();
                birdCount++;
            }
        }
        return (averageFlightSpeed / birdCount);
    }
}


/**
 *             Actor actor = field.getActorAt(where);
            if(actor instanceof Prey && !(actor instanceof Predator)) {
                Actor rabbit = (Prey) actor;
                if(rabbit.isAlive()) { 
                    rabbit.setDead();
                    foodLevel = RABBIT_FOOD_VALUE;
                    return where;
                }
 */