import java.util.Set;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Arrays;

/**
 * This is the player class. It keeps track of a player's inventory
 * and how much money they have.
 * 
 * is only designed to retrieve data on specific items.
 * 
 * @author Steffen L. Norgren 
 * @version 2007.08.05
 */
public class Player
{
    private double wallet;
    private HashMap<String, Item> inventory;
    private static final String[] requiredItems = {"textbook", "notebook",
                                                   "pen", "identification"};
    
    /**
     * Create a player.
     */
    public Player()
    {
        this.wallet = 0;
        inventory = new HashMap<String, Item>();
    }
        
    /**
     * Get the amount of money in the player's wallet
     * @return String items weight in kilograms
     */
    public double getBalance()
    {
        return wallet;
    }
    
    /**
     * Add money to the player's wallet
     * @param double money to add to the player
     */
    public void addMoney(double money)
    {
        // only positive values to the wallet
        if(money > 0) {
            this.wallet += money;
        }
    }
    
    /**
     * Remove money from the player's wallet.
     * @param double money to remove from the player
     */
    public void spendMoney(double money)
    {
        // make sure there is enough money in the wallet
        if(money <= wallet && money > 0) {
            this.wallet -= money;
        }
    }
    
    
    /**
     * Add an item to the player's inventory.
     * @param Item item object to put in the player's inventory
     */
    public void takeItem(Item item)
    {
        inventory.put(item.getItemName(), item);
    }
    
    /**
     * Remove an item from the player's inventory and return
     * the item object.
     * @param String item name
     * @return item object
     */
    public Item dropItem(String itemName)
    {
        Item item = inventory.get(itemName);
        
        if(item != null) {
            inventory.remove(itemName);
            return item;
        }
        else {
            return null;
        }
    }
    
    /**
     * Returns the total weight of all items in the player's
     * inventory.
     */
    public double inventoryWeight()
    {
        double returnWeight = 0;
        
        Set<String> keys = inventory.keySet();
        for(String item : keys) {
            returnWeight += inventory.get(item).getWeightKG();
        }
        
        return returnWeight;
    }
    
    /**
     * Returns a string items in the player's inventory.
     */
    public String inventoryList()
    {
        String returnString = "Inventory:";
        String seperator = " ";
        int count = 0;
        
        Set<String> keys = inventory.keySet();
        for(String item : keys) {
            if (count > 0) { // changes the seperator to a comma after first item
                seperator = ", ";
            }
            returnString += seperator + item;
            count++;
        }
        
        // return a blank line if there are no items in the inventory
        if(count != 0) {
            return returnString + ", $" + wallet + "\n";
        }
        else { // print your money as part of the inventory
            return "Inventory: $" + wallet + "\n";
        }
    }
    
    /**
     * Returns true or false depending on whether the player has
     * all of the required items to win the game.
     */
    public boolean allRequiredItems()
    {
        int totalNeeded = 0;
        
        Set<String> keys = inventory.keySet();
        for(String item : keys) {
            for(int i = 0; i < requiredItems.length; i++) {
                if(item.equals(requiredItems[i])) {
                    totalNeeded++;
                }
            }
        }
        
        if(totalNeeded >= requiredItems.length) {
            return true;
        }
        else {
            return false;
        }
    }
}