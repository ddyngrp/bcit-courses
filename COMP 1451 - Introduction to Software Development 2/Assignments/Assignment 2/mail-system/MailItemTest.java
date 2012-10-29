

/**
 * The test class MailItemTest.
 *
 * @author  (your name)
 * @version (a version number or a date)
 */
public class MailItemTest extends junit.framework.TestCase
{
    private MailItem mailItem = new MailItem("Steffen",
                                             "Lars",
                                             "Nameless Empty Void",
                                             "Lets talk about the schwartzchild radius!");
    
    /**
     * Default constructor for test class MailItemTest
     */
    public MailItemTest()
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

    public void testGetTo()
    {
        assertEquals("Lars", mailItem.getTo());
    }

    public void testGetFrom()
    {
        assertEquals("Steffen", mailItem.getFrom());
    }
    
    public void testGetSubject()
    {
        assertEquals("Nameless Empty Void", mailItem.getSubject());
    }

    public void testGetMessage()
    {
        assertEquals("Lets talk about the schwartzchild radius!", mailItem.getMessage());
    }
}


