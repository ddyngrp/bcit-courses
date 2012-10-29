

/**
 * The test class RoomTest.
 *
 * @author  (your name)
 * @version (a version number or a date)
 */
public class RoomTest extends junit.framework.TestCase
{
    /**
     * Default constructor for test class RoomTest
     */
    public RoomTest()
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
     * Test whether the returned room equals the one we created
     */
	public void testRoomReturn()
	{
		Room room = new Room("strange room");
		room.setExit("north", room);
		Room returnedRoom = room.getExit("north");
		assertEquals(returnedRoom, room.getExit("north"));
	}
}

