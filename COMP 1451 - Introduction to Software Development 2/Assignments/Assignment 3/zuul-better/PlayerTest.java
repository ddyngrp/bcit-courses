

/**
 * The test class PlayerTest.
 *
 * @author  (your name)
 * @version (a version number or a date)
 */
public class PlayerTest extends junit.framework.TestCase
{
    public Player player = new Player();
    public Item item1 = new Item("textbook", 2, 1, true);
    public Item item2 = new Item("pen", 2, 1, true);
    public Item item3 = new Item("identification", 2, 1, true);
    public Item item4 = new Item("notebook", 2, 1, true);
    
    /**
     * Default constructor for test class PlayerTest
     */
    public PlayerTest()
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
     * Test the player's initial balance
     */
    public void testInitialBalance()
    {
        assertEquals(0.0, player.getBalance());
    }

    /**
     * Test adding money to the player's wallet
     */
    public void testAddMoney()
    {
        player.addMoney(20);
        assertEquals(20.0, player.getBalance());
        player.addMoney(-20);
        assertEquals(20.0, player.getBalance());
    }
    
    /**
     * Test subtracting money from the player's wallet
     */
    public void testSubtractMoney()
    {
        player.addMoney(20);
        player.spendMoney(10.0);
        assertEquals(10.0, player.getBalance());
        player.spendMoney(-10.0);
        assertEquals(10.0, player.getBalance());
    }
    
    /**
     * Test the total weight of the player's inventory
     */
    public void testInventoryWeight()
    {
        player.takeItem(item1);
        assertEquals(2.0, player.inventoryWeight());
        player.takeItem(item2);
        assertEquals(4.0, player.inventoryWeight());
        player.takeItem(item3);
        assertEquals(6.0, player.inventoryWeight());
        player.takeItem(item4);
        assertEquals(8.0, player.inventoryWeight());
    }
    
    /**
     * Test whether the player has all the required items
     */
    public void testRequiredItems()
    {
        player.takeItem(item1);
        assertEquals(false, player.allRequiredItems());
        player.takeItem(item2);
        assertEquals(false, player.allRequiredItems());
        player.takeItem(item3);
        assertEquals(false, player.allRequiredItems());
        player.takeItem(item4);
        assertEquals(true, player.allRequiredItems());
    }
}



