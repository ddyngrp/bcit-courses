

/**
 * The test class ItemTest.
 *
 * @author  (your name)
 * @version (a version number or a date)
 */
public class ItemTest extends junit.framework.TestCase
{
    public Item item1 = new Item("item", 1.3, 2.1, true);
    
    /**
     * Default constructor for test class ItemTest
     */
    public ItemTest()
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
     * Test wether the values in the item object reflect the
     * ones we input.
     */
    public void testItem()
    {
        assertEquals(true, item1.getCanCarry());
        assertEquals(2.1, item1.getCost());
        assertEquals("item", item1.getItemName());
        assertEquals(1.3, item1.getWeightKG());
    }
    
    /**
     * Test whether setting a new cost works.
     */
    public void testCost()
    {
        item1.setCost(2);
        assertEquals(2.0, item1.getCost());
    }
}

