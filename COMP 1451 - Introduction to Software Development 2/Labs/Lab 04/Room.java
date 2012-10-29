import java.util.HashMap;
import java.util.Set;

/**
 * Class Room - a room in an adventure game.
 *
 * This class is part of the "World of Zuul" application. 
 * "World of Zuul" is a very simple, text based adventure game.  
 *
 * A "Room" represents one location in the scenery of the game.  It is 
 * connected to other rooms via exits.  The exits are labelled north, 
 * east, south, west.  For each direction, the room stores a reference
 * to the neighboring room, or null if there is no exit in that direction.
 * 
 * @author  Michael Kolling and David J. Barnes
 * @version 2006.03.30
 */
public class Room 
{
    private String description;
    private HashMap<String, Room> exits;
    
    /**
     * Create a room described "description". Initially, it has
     * no exits. "description" is something like "a kitchen" or
     * "an open court yard".
     * @param description The room's description.
     */
    public Room(String description) 
    {
        this.description = description;
        exits = new HashMap<String, Room>();
    }

    /**
     * Define the exits of this room.
     * 
     * @param direction The direction of the exit.
     * @param neighbour The room in the given direction.
     */
    public void setExit(String direction, Room neighbour) 
    {
        exits.put(direction, neighbour);
    }

    /**
     * @return The description of the room.
     */
    public String getDescription()
    {
        return description;
    }
    
    /**
     * Return the room that is reached if we go from this
     * room in direction "direction". If there is no room in
     * that direction, return null.
     * 
     * @param direction the direction we want to go
     */
    public Room getExit(String direction)
    {
        return exits.get(direction);
    }
    
    /**
     * Return a description of the room's exits,
     * for example, "Exits: north west".
     * @return A description of the available exits.
     */
    public String getExitString()
    {
        String exitString = "Exits:";
        
        Set<String> keys = exits.keySet();
        
        for(String exit : keys)
            exitString += " " + exit;
            
        return exitString;
    }
}
