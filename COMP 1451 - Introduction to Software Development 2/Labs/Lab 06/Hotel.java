import java.util.ArrayList;
import java.util.Iterator;

/**
 * Write a description of class Hotel here.
 * 
 * @author Steffen L. Norgren
 * @version July 29, 2007
 */
public class Hotel
{
    private ArrayList<Animals> animals;
    
    /**
     * Constructor for objects of class Hotel
     */
    public Hotel()
    {
        animals = new ArrayList<Animals>();
    }
    
    /**
     * New Guest in the hotel
     */
    public void addGuest(Animals animal)
    {
        animals.add(animal);
    }
    
    public void listAllGuests()
    {
        for(Animals animal : animals) {
            System.out.println(animal);
        }
    }
}
