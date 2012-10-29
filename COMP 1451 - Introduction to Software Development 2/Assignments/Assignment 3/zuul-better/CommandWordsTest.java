

/**
 * The test class CommandWordsTest.
 *
 * @author  (your name)
 * @version (a version number or a date)
 */
public class CommandWordsTest extends junit.framework.TestCase
{
    public CommandWords commandWords = new CommandWords();
    
    /**
     * Default constructor for test class CommandWordsTest
     */
    public CommandWordsTest()
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
     * Tests whether all the command words are properly recognized.
     */
    public void testCommands()
    {
        assertEquals(true, commandWords.isCommand("go"));
        assertEquals(true, commandWords.isCommand("quit"));
        assertEquals(true, commandWords.isCommand("help"));
        assertEquals(true, commandWords.isCommand("take"));
        assertEquals(true, commandWords.isCommand("drop"));
        assertEquals(true, commandWords.isCommand("buy"));
        assertEquals(true, commandWords.isCommand("back"));
    }
}

