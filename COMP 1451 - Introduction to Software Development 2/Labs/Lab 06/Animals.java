
/**
 * Write a description of class Animals here.
 * 
 * @author Steffen L. Norgren
 * @version July 29, 2007
 */
public class Animals
{
    private String breed;
    private double weightKG;

    public Animals(String theBreed, double theWeightKG)
    {
        breed = theBreed;
        weightKG = theWeightKG;
    }
    
    public void setBreed(String theBreed)
    {
        breed = theBreed;
    }
    
    public void setWeightKG(double theWeightKG)
    {
        weightKG = theWeightKG;
    }
    
    public String getBreed()
    {
        return breed;
    }
    
    public double getWeightKG()
    {
        return weightKG;
    }
    
    public String toString()
    {
        return "This is a " + getBreed() + " weighing "
               + getWeightKG() + " kilos.";
    }
}
