import java.util.Random;
import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Collections;
import java.awt.Color;

/**
 * A simple predator-prey simulator, based on a field containing
 * rabbits and foxes.
 * 
 * @author David J. Barnes, Michael Kolling, and Steffen L. Norgren
 * @version 2007.08.14
 */
public class Simulator
{
    // Constants representing configuration information for the simulation.
    // The default width for the grid.
    private static final int DEFAULT_WIDTH = 50;
    // The default depth of the grid.
    private static final int DEFAULT_DEPTH = 50;
    // The default number of trapping licenses issued.
    private static final int DEFAULT_LICENCES = 1;
    // The default minimum of foxes that can be trapped.
    private static final int DEFAULT_MIN_FOXES_TRAPPED = 1;
    // The default maximum of foxes that can be trapped.
    private static final int DEFAULT_MAX_FOXES_TRAPPED = 1000;
    // The probability that a fox will be created in any given grid position.
    private static final double FOX_CREATION_PROBABILITY = 0.02;
    // The probability that a rabbit will be created in any given grid position.
    private static final double RABBIT_CREATION_PROBABILITY = 0.08;

    // The list of actors in the field
    private List<Actor> actors;
    // The list of actors just born
    private List<Actor> newActors;
    // List of stats involving deaths
    private List<String> deathStats;
    // The current state of the field.
    private Field field;
    // A second field, used to build the next stage of the simulation.
    private Field updatedField;
    // The current step of the simulation.
    private int step;
    // A graphical view of the simulation.
    private SimulatorView view;
    // The number of trapping licences issued.
    private int trappingLicences;
    // The minimum number of foxes that a trapper can trap.
    private int minFoxesTrapped;
    // The maximum number of foxes that a trapper can trap.
    private int maxFoxesTrapped;

    /**
     * Construct a simulation field with default size.
     */
    public Simulator()
    {
        this(DEFAULT_DEPTH, DEFAULT_WIDTH, DEFAULT_LICENCES,
             DEFAULT_MIN_FOXES_TRAPPED, DEFAULT_MAX_FOXES_TRAPPED);
    }
    
    /**
     * Create a simulation field with the given size.
     * @param depth Depth of the field. Must be greater than zero.
     * @param width Width of the field. Must be greater than zero.
     * @param trappingLicences number of trapping licenses to issue.
     * @param minFoxesTrapped minimum number of foxes to trap to retain a license
     * @param maxFoxesTrapped maximum number of foxes allowed to be trapped
     */
    public Simulator(int depth, int width, int trappingLicences,
                     int minFoxesTrapped, int maxFoxesTrapped)
    {
        if(width <= 0 || depth <= 0) {
            System.out.println("The dimensions must be greater than zero.");
            System.out.println("Using default values.");
            depth = DEFAULT_DEPTH;
            width = DEFAULT_WIDTH;
        }
        
        if(trappingLicences < 0) {
            System.out.println("The number of trapping licenses must be " +
                               "greater than zero.");
            System.out.println("Using default values.");
            trappingLicences = DEFAULT_LICENCES;
        }

        if(minFoxesTrapped < 0 || maxFoxesTrapped <= minFoxesTrapped) {
            System.out.println("The minimum & maximum amount of foxes trapped " +
                               "must be greater than zero.");
            System.out.println("Using default values.");
            minFoxesTrapped = DEFAULT_MIN_FOXES_TRAPPED;
            maxFoxesTrapped = DEFAULT_MAX_FOXES_TRAPPED;
        }
        
        actors = new ArrayList<Actor>();
        newActors = new ArrayList<Actor>();
        deathStats = new ArrayList<String>();
        field = new Field(depth, width);
        updatedField = new Field(depth, width);
        
        // Set trapping conditions
        this.trappingLicences = trappingLicences;
        this.minFoxesTrapped = minFoxesTrapped;
        this.maxFoxesTrapped = maxFoxesTrapped;

        // Create a view of the state of each location in the field.
        view = new SimulatorView(depth, width);
        view.setColor(Trapper.class, Color.black);
        view.setColor(Rabbit.class, Color.orange);
        view.setColor(Fox.class, Color.blue);

        // Setup a valid starting point.
        reset();
    }
    
    /**
     * Run the simulation from its current state for a reasonably long period,
     * e.g. 500 steps.
     */
    public void runLongSimulation()
    {
        simulate(500);
    }
    
    /**
     * Run the simulation from its current state for the given number of steps.
     * Stop before the given number of steps if it ceases to be viable.
     * @param numSteps How many steps to run for.
     */
    public void simulate(int numSteps)
    {
        for(int step = 1; step <= numSteps && view.isViable(field); step++) {
            simulateOneStep();
        }
        printStats();
    }
    
    /**
     * Run the simulation from its current state for a single step.
     * Iterate over the whole field updating the state of each
     * fox and rabbit.
     */
    public void simulateOneStep()
    {
        step++;
        newActors.clear();
        
        // let all actors act
        for(Iterator<Actor> it = actors.iterator(); it.hasNext(); ) {
            Actor actor = it.next();
            actor.act(field, updatedField, newActors, deathStats);
            // Remove dead actors from the simulation.
            if(! actor.isAlive()) {
                it.remove();
            }
        }
        // add new born actors to the list of actors
        actors.addAll(newActors);
        
        // Swap the field and updatedField at the end of the step.
        Field temp = field;
        field = updatedField;
        updatedField = temp;
        updatedField.clear();

        // Display the new field on screen.
        view.showStatus(step, field);
    }
        
    /**
     * Reset the simulation to a starting position.
     */
    public void reset()
    {
        step = 0;
        actors.clear();
        newActors.clear();
        field.clear();
        updatedField.clear();
        deathStats.clear();
        populate(field);
        
        // Show the starting state in the view.
        view.showStatus(step, field);
    }
    
    /**
     * Populate a field with foxes and rabbits.
     * @param field The field to be populated.
     */
    private void populate(Field field)
    {
        Random rand = new Random();
        field.clear();
        for(int row = 0; row < field.getDepth(); row++) {
            for(int col = 0; col < field.getWidth(); col++) {
                if(rand.nextDouble() <= FOX_CREATION_PROBABILITY) {
                    Actor fox = new Fox(true);
                    fox.setLocation(row, col);
                    actors.add(fox);
                    field.place(fox);
                }
                else if(rand.nextDouble() <= RABBIT_CREATION_PROBABILITY) {
                    Actor rabbit = new Rabbit(true);
                    rabbit.setLocation(row, col);
                    actors.add(rabbit);
                    field.place(rabbit);
                }
                // else leave the location empty.
            }
        }
        // place the trappers randomly around the field
        for(int licences = 0; licences < trappingLicences; licences++) {
            Actor trapper = new Trapper(true, minFoxesTrapped, maxFoxesTrapped);
            trapper.setLocation(rand.nextInt(field.getDepth()),
                                rand.nextInt(field.getWidth()));
            actors.add(trapper);
            field.place(trapper);            
        }        
        Collections.shuffle(actors);
    }
    
    /**
     * Print out statistics at the end of each simulation run.
     */
    public void printStats()
    {
        // set all counters to zero
        int retired = 0;
        int futile = 0;
        int trapped = 0;
        int overcrowded = 0;
        int oldage = 0;
        
        // iterate through my hack of a List to search for events
        for(Iterator<String> it = deathStats.iterator(); it.hasNext(); ) {
            String deathStats = it.next();
            
            if(deathStats.equals("retired")) {
                retired++;
            }
            if(deathStats.equals("futile")) {
                futile++;
            }
            if(deathStats.equals("trapped")) {
                trapped++;
            }
            if(deathStats.equals("overcrowded")) {
                overcrowded++;
            }
            if(deathStats.equals("oldage")) {
                oldage++;
            }
        }
        
        System.out.println("Fox Deaths due to trapping: " + trapped);
        System.out.println("Fox Deaths due to overcrowding: " + overcrowded);
        System.out.println("Fox Deaths due to old age: " + oldage);
        System.out.println("Trappers that retired: " + retired);
        System.out.println("Trappers that didn't meet minimum quota: " + futile);
    }
}