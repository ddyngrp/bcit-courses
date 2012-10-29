

/**
 * The test class BankTest.
 *
 * @author  (your name)
 * @version (a version number or a date)
 */
public class BankTest extends junit.framework.TestCase
{
    /**
     * Default constructor for test class BankTest
     */
    public BankTest()
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

	public void testBank()
	{
		Bank bank1 = new Bank();
		BankAccount bankAcco1 = new BankAccount("Steffen", 1000);
		bank1.openAccount("One");
		bank1.openAccount("Two", 900);
		bank1.openAccount(bankAcco1);
		bank1.showAccountInfo();
		bank1.applyInterest();
		bank1.showAccountInfo();
		assertEquals(3, bank1.numberOfAccounts());
		bank1.removeAccount(1);
		bank1.showAccountInfo();
	}
}





