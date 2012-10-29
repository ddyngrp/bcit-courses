
/**
 * Write a description of class Tree here.
 * 
 * @author Steffen L. Norgren
 * @version June 5, 2007
 */
public class Tree
{
    private String treeSpecies;
    private int treeAgeInYears;
    
    /**
     * Default constructor for Tree
     */
    public Tree( String newTreeSpecies, int newTreeAgeInYears )
    {
        treeSpecies = newTreeSpecies;
        treeAgeInYears = newTreeAgeInYears;
    }
    
    /**
     * Getter for treeSpecies
     */
    public String getTreeSpecies()
    {
        return treeSpecies;
    }
    
    /**
     * Getter for treeAgeInYears
     */
    public int getTreeAgeInYears()
    {
        return treeAgeInYears;
    }
}
