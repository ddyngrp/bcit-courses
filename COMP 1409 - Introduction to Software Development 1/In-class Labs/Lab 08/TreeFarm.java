
/**
 * Write a description of class TreeFarm here.
 * 
 * @author Steffen L. Norgren
 * @version June 5, 2007
 */

import java.util.ArrayList;
import java.util.Iterator;

public class TreeFarm
{
    // ArrayList for Tree objects
    private ArrayList<Tree> treeFarm;
    
    /**
     * Default constructor for TreeFarm
     */
    public TreeFarm()
    {
        treeFarm = new ArrayList<Tree>();
    }
    
    /**
     * takes one parameter of type Tree and adds an existing
     * Tree object to the treeFarm.
     */
    public void addTree( Tree newTree )
    {
        treeFarm.add( newTree );
    }
    
    /**
     * Shows all trees and displays the species and age of each
     */
    public void showAllTrees()
    {
        // iterator object for Tree
        Iterator<Tree> tree = treeFarm.iterator();
        
        // loop through tree objects within treeFarm
        while ( tree.hasNext() )
        {
            Tree currentTree = tree.next();
            System.out.println( "Species: " + currentTree.getTreeSpecies() + 
                                " Age: " + currentTree.getTreeAgeInYears() );
        } // end while loop
    }
    
    /**
     * removes from the treeFarm all the trees whose
     * age is grater than the parameter
     */
    public void logOldTrees( int maxTreeAge )
    {
        // iterator object for Tree
        Iterator<Tree> tree = treeFarm.iterator();
        
        // loop through tree objects within treeFarm
        while ( tree.hasNext() )
        {
            Tree currentTree = tree.next();
            if ( currentTree.getTreeAgeInYears() > maxTreeAge )
            {
                tree.remove();
            } // end if
        } // end while loop
    }
    
    /**
     * checks to make sure that the two int parameters are valid index
     * positions within the treeFarm. If not, it displays an error, otherwise
     * it will switch the position of the two trees at these index positions.
     */
    public void swap( int xTree, int yTree )
    {
        // Temporary object
        Tree tempTree = treeFarm.get( xTree );
        
        if ( treeFarm.size() < xTree || yTree > treeFarm.size()
             || xTree < 0 || yTree < 0 )
        {
            System.out.println("I'm sorry Dave, but I can't do that.");
        }
        else
        {
            // Sets the xTree position to the value of yTree
            treeFarm.set( xTree, treeFarm.get( yTree ) );
            // Sets the yTree position to the temporary object
            treeFarm.set( yTree, tempTree );
        }
    }
}
