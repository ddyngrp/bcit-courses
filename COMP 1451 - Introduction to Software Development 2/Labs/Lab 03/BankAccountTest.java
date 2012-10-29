

/**
 * The test class BankAccountTest.
 *
 * @author  (your name)
 * @version (a version number or a date)
 */
public class BankAccountTest extends junit.framework.TestCase
{
    /**
     * Default constructor for test class BankAccountTest
     */
    public BankAccountTest()
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

	public void testNoMoneyBankAcount()
	{
		BankAccount bankAcco1 = new BankAccount("Steffen");
		bankAcco1.deposit(1000);
		assertEquals(1000.0, bankAcco1.getBalance());
		bankAcco1.withdraw(900);
		assertEquals(100.0, bankAcco1.getBalance());
		assertEquals("Steffen", bankAcco1.getCustomerName());
		bankAcco1.applyInterest();
		assertEquals(101.0, bankAcco1.getBalance());
	}

	public void testMoneyBankAccount()
	{
		BankAccount bankAcco1 = new BankAccount("Steffen", 1000);
		assertEquals(1000.0, bankAcco1.getBalance());
		bankAcco1.deposit(1000);
		assertEquals(2000.0, bankAcco1.getBalance());
		assertEquals("Steffen", bankAcco1.getCustomerName());
		bankAcco1.withdraw(1000);
		assertEquals(1000.0, bankAcco1.getBalance());
		bankAcco1.applyInterest();
		assertEquals(1010.0, bankAcco1.getBalance());
		bankAcco1.applyInterest();
		assertEquals(1020.1, bankAcco1.getBalance());
	}

	public void testMultipleAccounts()
	{
		BankAccount bankAcco1 = new BankAccount("One");
		BankAccount bankAcco2 = new BankAccount("Two");
		BankAccount bankAcco3 = new BankAccount("Three");
		assertEquals(bankAcco1.getAccountNumber() + 1, bankAcco2.getAccountNumber());
		assertEquals(bankAcco2.getAccountNumber() + 1, bankAcco3.getAccountNumber());
	}
}





