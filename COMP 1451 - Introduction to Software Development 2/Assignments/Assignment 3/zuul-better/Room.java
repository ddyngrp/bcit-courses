import java.util.Set;
import java.util.HashMap;
import java.util.Iterator;

/**
 * Class Room - a room in an adventure game.
 *
 * This class is part of the "World of Zuul" application. 
 * "World of Zuul" is a very simple, text based adventure game.  
 *
 * A "Room" represents one location in the scenery of the game.  It is 
 * connected to other rooms via exits.  For each existing exit, the room 
 * stores a reference to the neighboring room.
 * 
 * @author Michael Kolling, David J. Barnes and Steffen L. Norgren
 * @version 2007.08.05
 */

public class Room
{
    private String description;
    private HashMap<String, Room> exits;    // stores exits of this room
    private HashMap<String, Item> items;    // stores item objects for this room

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
        items = new HashMap<String, Item>();
    }
    
    /**
     * Define an exit from this room.
     * @param direction The direction of the exit.
     * @param neighbor  The room to which the exit leads.
     */
    public void setExit(String direction, Room neighbor) 
    {
        exits.put(direction, neighbor);
    }
    
    /**
     * Create an item and store it in this object's ArrayList.
     * @param itemDesc description of the item.
     * @param weightKG weight of the item in kilograms.
     * @param canCarry whether the item can be carried.
     */
    public void createItem(String itemName, double weightKG,
                        double cost, boolean canCarry)
    {
        items.put(itemName, new Item(itemName, weightKG, cost, canCarry));
    }
    
    /**
     * Put an item in the current room.
     * @param Item item object you want to store.
     */
    public void putItem(Item item)
    {
        items.put(item.getItemName(), item);
    }
    
    /**
     * Remove an item from a room and return the object.
     * @param itemName the name of the item you wish to remove
     * @return the item object removed
     */
    public Item takeItem(String itemName)
    {
        Item item = items.get(itemName);
        
        if (item == null) {
            return null;
        }
        else {
            items.remove(itemName);
            return item;
        }
    }
    
    /**
     * @return The short description of the room
     * (the one that was defined in the constructor).
     */
    public String getShortDescription()
    {
        return description;
    }

    /**
     * Return a description of the room in the form:
     *     You are in the kitchen.
     *     Items: knife bread sheep
     *     Exits: north west
     * @return A long description of this room
     */
    public String getLongDescription()
    {
        return "You are " + description + "." + getItemString() +
               "\n" + getExitString();
    }
    
    /**
     * Return a string describing the items in the room, for example
     * "Items: knife bread sheep"
     * @return Details of the room's items.
     */
    private String getItemString()
    {
        String returnString = "Items:";
        String seperator = " ";
        int count = 0;
        
        Set<String> keys = items.keySet();
        for (String item : keys) {
            if (count > 0) { // changes the seperator to a comma after first item
                seperator = ", ";
            }
            returnString += seperator + item;
            // attach a cost descriptor to the item if it has a cost or value
            if (items.get(item).getCost() != 0) {
                returnString += " ($" + items.get(item).getCost() + ")";
            }
            count++;
        }
        
        // return a blank if there are no items in the room
        if (count != 0) {
            return "\n" + returnString;
        }
        else {
            return "";
        }
    }
    
    /**
     * Return a string describing the room's exits, for example
     * "Exits: north west".
     * @return Details of the room's exits.
     */
    private String getExitString()
    {
        String returnString = "Exits:";
        Set<String> keys = exits.keySet();
        for (String exit : keys) {
            if(!exit.equals("exam")) {
                returnString += " " + exit;
            }
        }
        return returnString;
    }

    /**
     * Return the room that is reached if we go from this room in direction
     * "direction". If there is no room in that direction, return null.
     * @param direction The exit's direction.
     * @return The room in the given direction.
     */
    public Room getExit(String direction) 
    {
        return exits.get(direction);
    }
}

