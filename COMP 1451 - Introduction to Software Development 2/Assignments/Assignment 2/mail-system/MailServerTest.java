

/**
 * The test class MailServerTest.
 *
 * @author  (your name)
 * @version (a version number or a date)
 */
public class MailServerTest extends junit.framework.TestCase
{
    private MailServer Server = new MailServer();
    private MailClient Steffen = new MailClient(Server, "Steffen");
    private MailClient Lars = new MailClient(Server, "Lars");    

    /**
     * Default constructor for test class MailServerTest
     */
    public MailServerTest()
    {
    }

    /**
     * Sets up the test fixture.
     *
     * Called before every test case method.
     */
    protected void setUp()
    {
        // 2 spam, 3 real
        Steffen.sendMailItem("Lars", "Spam", "Message 1");
        Steffen.sendMailItem("Lars", "Not spam", "Message 2");
        Steffen.sendMailItem("Lars", "Hello", "Message 3");
        Steffen.sendMailItem("Lars", "This deal for you", "Message 4");
        Steffen.sendMailItem("Lars", "Deliciousness", "Message 5");

        // 2 spam 2 real
        Lars.sendMailItem("Steffen", "Did you get that SPAM?", "Message 1");
        Lars.sendMailItem("Steffen", "Well now!", "Message 2");
        Lars.sendMailItem("Steffen", "We have hot news", "Message 3");
        Lars.sendMailItem("Steffen", "I have kittah pix and cheap drugs", "Message 4");
    }

    /**
     * Tears down the test fixture.
     *
     * Called after every test case method.
     */
    protected void tearDown()
    {
    }

    public void testPositiveSpamChecker()
    {
        assertEquals(true, Server.spamChecker("SPAM"));
        assertEquals(true, Server.spamChecker("cheap drugs"));
        assertEquals(true, Server.spamChecker("deal for you"));
        assertEquals(true, Server.spamChecker("loan request"));
        assertEquals(true, Server.spamChecker("hot news"));
        
        assertEquals(true, Server.spamChecker("spam this may be"));
        assertEquals(true, Server.spamChecker("We have Cheap DRUGS for you"));
        assertEquals(true, Server.spamChecker("This deal for YOU"));
        assertEquals(true, Server.spamChecker("Your loan Request application"));
        assertEquals(true, Server.spamChecker("Deliciously HOT news from Canada"));
    }
    
    public void testNegativeSpamChecker()
    {
        assertEquals(false, Server.spamChecker("S.P.A.M."));
        assertEquals(false, Server.spamChecker("cheep drogs"));
        assertEquals(false, Server.spamChecker("deal 4 you"));
        assertEquals(false, Server.spamChecker("loan bequest"));
        assertEquals(false, Server.spamChecker("cold news"));
        
        assertEquals(false, Server.spamChecker("this may be spam possibly"));
        assertEquals(false, Server.spamChecker("We have Cheep DRUGS for you"));
        assertEquals(false, Server.spamChecker("This deal 4 YOU"));
        assertEquals(false, Server.spamChecker("Your loan bequest application"));
        assertEquals(false, Server.spamChecker("Deliciously cold news from Canada"));
    }
    
    public void testFirstToUpper()
    {
        assertEquals("This Is A String Of Some Length", 
                    Server.firstToUpper("this is a string of some length"));

    }

    public void testHowManyMailItems()
    {
		assertEquals(3, Server.howManyMailItems("Lars"));
		assertEquals(2, Server.howManyMailItems("Steffen"));
		assertEquals(0, Server.howManyMailItems("nonexistenta"));
    }
    
    public void testNextMailItem()
    {
        assertNotNull(Server.getNextMailItem("Lars"));
		assertEquals(2, Server.howManyMailItems("Lars"));
		
		assertNotNull(Server.getNextMailItem("Steffen"));
		assertEquals(1, Server.howManyMailItems("Steffen"));
		
		assertNull(Server.getNextMailItem("nonexistenta"));
		assertEquals(0, Server.howManyMailItems("nonexistenta"));
    }
}


