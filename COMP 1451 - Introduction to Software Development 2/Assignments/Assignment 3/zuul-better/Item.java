/**
 * This class deals with created items. It is a simple class, which
 * is only designed to retrieve data on specific items.
 * 
 * @author Steffen L. Norgren 
 * @version 2007.08.05
 */
public class Item
{
    private String itemName;
    private double weightKG;
    private double cost;
    private boolean canCarry;
    
    /**
     * Create an item.
     * @param itemName description of the item.
     * @param weightKG weight of the item in kilograms.
     * @param cost the cost of the item in dollars.
     * @param canCarry whether the item can be carried.
     */
    public Item(String itemName, double weightKG,
                double cost, boolean canCarry)
    {
        this.itemName = itemName;
        this.weightKG = weightKG;
        this.cost = cost;
        this.canCarry = canCarry;
    }
    
    /**
     * Getter for description
     * @return String item description
     */
    public String getItemName()
    {
        return itemName;
    }
    
    /**
     * Getter for weightKG
     * @return String items weight in kilograms
     */
    public double getWeightKG()
    {
        return weightKG;
    }

    /**
     * Getter for canCarry
     * @return boolean whether item can be carried
     */
    public boolean getCanCarry()
    {
        return canCarry;
    }

    /**
     * Getter for cost
     * @return String item's cost in dollars
     */
    public double getCost()
    {
        return cost;
    }
    
    /**
     * Setter for cost
     * @param double the items new cost
     */
    public void setCost(double cost)
    {
        if(cost >= 0)
        {
            this.cost = cost;
        }
    }
}
