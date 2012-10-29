
/**
 * Write a description of class Dog here.
 * 
 * @author Steffen L. Norgren
 * @version July 29, 2007
 */
public class Dog extends Animals
{
    private boolean walks;

    public Dog(String theBreed, double theWeightKG, boolean walksYN)
    {
        super(theBreed, theWeightKG);
        walks = walksYN;
    }
    
    public void setWalks(boolean walksYN)
    {
        walks = walksYN;
    }
    
    public boolean getWalks()
    {
        return walks;
    }

    public String toString()
    {
        String string = "This ";
        
        if(walks) {
            string += "dog likes to walk.";
        }
        else {
            string += "a lazy dog!";
        }

        return super.toString() + '\n' + string;
    }
}
