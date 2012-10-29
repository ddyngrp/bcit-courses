

/**
 * The test class CommandTest.
 *
 * @author  (your name)
 * @version (a version number or a date)
 */
public class CommandTest extends junit.framework.TestCase
{
    /**
     * Default constructor for test class CommandTest
     */
    public CommandTest()
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

    /**
     * Testing whether the Command class properly recognizes a known command
     * word along with a second word.
     */
	public void testTwoKnown()
	{
		Command commands = new Command("go", "north");
		assertEquals("go", commands.getCommandWord());
		assertEquals("north", commands.getSecondWord());
		assertEquals(true, commands.hasSecondWord());
		assertEquals(false, commands.isUnknown());
	}

    /**
     * Testing whether the Command class properly recognizes an unknown
     * command word along with a second word.
     */
	public void testTwoUnknown()
	{
		Command commands = new Command("drive", "north");
		assertEquals("drive", commands.getCommandWord());
		assertEquals("north", commands.getSecondWord());
		assertEquals(true, commands.hasSecondWord());
		assertEquals(false, commands.isUnknown());
	}
	
    /**
     * Testing whether the Command class properly recognizes a
     * single known command word
     */
	public void testOneKnown()
	{
		Command commands = new Command("go", null);
		assertEquals("go", commands.getCommandWord());
		assertEquals(null, commands.getSecondWord());
		assertEquals(false, commands.hasSecondWord());
		assertEquals(false, commands.isUnknown());
	}
	
    /**
     * Testing whether the Command class properly recognizes a
     * single unknown command word
     */
	public void testOneUnknown()
	{
		Command commands = new Command("run", null);
		assertEquals("run", commands.getCommandWord());
		assertEquals(null, commands.getSecondWord());
		assertEquals(false, commands.hasSecondWord());
		assertEquals(false, commands.isUnknown());
	}
}

