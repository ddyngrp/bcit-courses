

/**
 * The test class MailClientTest.
 *
 * @author  (your name)
 * @version (a version number or a date)
 */
public class MailClientTest extends junit.framework.TestCase
{
    private MailServer Server = new MailServer();
    private MailClient Steffen = new MailClient(Server, "Steffen");
    private MailClient Lars = new MailClient(Server, "Lars");
    
    /**
     * Default constructor for test class MailClientTest
     */
    public MailClientTest()
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

    public void testSending()
    {
        Steffen.sendMailItem("Lars", "Hell", "Please visit me here sometime");
        Lars.sendMailItem("Steffen", "Pit", "I've run out of despair");
    }
    
    public void testSendingToUnknown()
    {
        Steffen.sendMailItem("notLars", "Hell", "Please visit me here sometime");
        Lars.sendMailItem("notSteffen", "Pit", "I've run out of despair");
    }

	public void testGetNextMailItem()
	{
		Lars.sendMailItem("Steffen", "Hell", "Please visit me here sometime");
		assertEquals("Steffen", Steffen.getNextMailItem().getTo());
		
		Lars.sendMailItem("Steffen", "Hell", "Please visit me here sometime");
		assertEquals("Lars", Steffen.getNextMailItem().getFrom());

		Lars.sendMailItem("Steffen", "Hell", "Please visit me here sometime");
		assertEquals("Hell", Steffen.getNextMailItem().getSubject());

		Lars.sendMailItem("Steffen", "Hell", "Please visit me here sometime");
		assertEquals("Please visit me here sometime", Steffen.getNextMailItem().getMessage());
	}
}


