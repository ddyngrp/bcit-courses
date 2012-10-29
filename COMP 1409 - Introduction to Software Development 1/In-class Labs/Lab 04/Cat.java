
/**
 * Meow!
 * 
 * @author Steffen L. Norgren
 * @version May 8, 2007
 */
public class Cat
{
	private String catName;
	private int yearOfBirth;
	private double weightInPounds;

	/**
	 * Constructor for objects of class Cat
	 */
	public Cat( String newCatName, int newYearOfBirth, double newWeightInPounds )
	{
	    catName = newCatName;
	    yearOfBirth = newYearOfBirth;
	    weightInPounds = newWeightInPounds;
	}

	/**
	 * Getter for catName
	 */
	public String getCatName()
	{
		return catName;
	}

	/**
	 * Getter for yearOfBirth
	 */
	public int getYearOfBirth()
	{
		return yearOfBirth;
	}

	/**
	 * Getter for weightInPounds
	 */
	public double getWeightInPounds()
	{
		return weightInPounds;
	}
}