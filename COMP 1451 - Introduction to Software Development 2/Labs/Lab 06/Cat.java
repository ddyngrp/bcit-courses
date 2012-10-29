
/**
 * Write a description of class Cat here.
 * 
 * @author Steffen L. Norgren
 * @version July 29, 2007
 */
public class Cat extends Animals
{
    private boolean hunts;

    public Cat(String theBreed, double theWeightKG, boolean huntsYN)
    {
        super(theBreed, theWeightKG);
        hunts = huntsYN;
    }
    
    public void setHunts(boolean huntsYN)
    {
        hunts = huntsYN;
    }
    
    public boolean getHunts()
    {
        return hunts;
    }

    public String toString()
    {
        String string = "This is ";
        
        if(hunts) {
            string += "a hunter!";
        }
        else {
            string += "a lazy cat!";
        }

        return string + '\n' + super.toString();
    }
}
