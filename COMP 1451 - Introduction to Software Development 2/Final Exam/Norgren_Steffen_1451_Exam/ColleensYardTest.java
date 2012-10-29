

/**
 * The test class ColleensYardTest.
 *
 * @author  (your name)
 * @version (a version number or a date)
 */
public class ColleensYardTest extends junit.framework.TestCase
{
    ColleensYard colleensYard = new ColleensYard();
    Chickadee chickadee = new Chickadee("Black-capped chickadee", 2, 0.23, "blue", 45.0);
    Hummingbird hummingbird = new Hummingbird("Rufous hummingbird", 1, 0.3, "brown", 56.0);
    Bear bear = new Bear("Black bear", 4, 56.0, "black");
    Squirrel squirrel = new Squirrel("Western grey squirrel", 2, 0.5, "grey");
    Bat bat = new Bat("Small brown bat", 2, 0.5, "brown");
    
    /**
     * Default constructor for test class ColleensYardTest
     */
    public ColleensYardTest()
    {
    }

    /**
     * Sets up the test fixture.
     *
     * Called before every test case method.
     */
    protected void setUp()
    {
    }

    /**
     * Tears down the test fixture.
     *
     * Called after every test case method.
     */
    protected void tearDown()
    {
    }

	public void testAddAnimals()
	{
		colleensYard.addAnimal(hummingbird);
		colleensYard.addAnimal(squirrel);
		colleensYard.addAnimal(chickadee);
		colleensYard.addAnimal(bear);
		colleensYard.addAnimal(bat);
	}

	public void testAverageFlightSpeed()
	{
		testAddAnimals();
		assertEquals(50.5, colleensYard.averageFlightSpeed());
	}
}


