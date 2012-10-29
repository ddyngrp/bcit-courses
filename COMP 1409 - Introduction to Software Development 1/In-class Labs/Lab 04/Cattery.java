
/**
 * Meow hiss!
 * 
 * @author Steffen L. Norgren
 * @version May 8, 2007
 */
public class Cattery
{
	private Cat cat1;
	private Cat cat2;

	/**
	 * Constructor for objects of class Cattery
	 */
	public Cattery()
	{
		cat1 = new Cat( "Muffin", 1997, 12.4 );
		cat2 = new Cat( "Not a Cat", 2004, 0.1 );
	}
	
	public void oldestCatName()
	{
	    if ( cat1.getYearOfBirth() > cat2.getYearOfBirth() )
	    {
	        System.out.println( cat2.getCatName() + " is the oldest cat." );
	    }
	    else
	    {
	        System.out.println( cat1.getCatName() + " is the oldest cat." );
	    }
	}
	   
	public Cat heaviestCatObject()
	{
	    if ( cat1.getWeightInPounds() > cat2.getWeightInPounds() )
	    {
	        return cat1;
	    }
	    else
	    {
	        return cat2;
	    }
	}
}
