import java.util.ArrayList;

/**
 *  This class is the main class of the "World of Zuul" application. 
 *  "World of Zuul" is a very simple, text based adventure game.  Users 
 *  can walk around some scenery. That's all. It should really be extended 
 *  to make it more interesting!
 * 
 *  To play this game, create an instance of this class and call the "play"
 *  method.
 * 
 *  This main class creates and initialises all the others: it creates all
 *  rooms, items, creates the parser and starts the game.  It also evaluates and
 *  executes the commands that the parser returns.
 * 
 * @author Michael Kolling, David J. Barnes and Steffen L. Norgren
 * @version 2007.08.05
 */

public class Game 
{
    private Parser parser;
    private Room currentRoom;
    private Player player;
    private ArrayList<Room> roomHistory;             // stores the previous rooms
                                                     // the player was in
    private static final double MAX_CARRY_KG = 10.0; // the maximum weight a player
                                                     // can carry on his person
    
    /**
     * Create the game and initialise its internal map.
     * Also create the player and initialize the map of
     * where the player has been.
     */
    public Game() 
    {
        createRoomsAndItems();
        player = new Player();
        parser = new Parser();
        roomHistory = new ArrayList<Room>();
    }

    /**
     * Create all the rooms and link their exits together.
     * Also create items attached to particular rooms.
     */
    private void createRoomsAndItems()
    {
        Room outside, store, pub, bookstore, security, courtyard, garden, entry,
             compLab, commons, instOffices, adminOffice, examRoom, corridor;
        
        // create the rooms
        outside =       new Room("outside. It is raining heavily and you're very wet.\n" +
                                 "The university ahead looks delapidated");
        entry =         new Room("in the entry way to the university. This is a vey\n" +
                                 "boring room. A sign advertises a local escort agency");
        security =      new Room("in the security office. There is a very fat man\n" +
                                 "here eating pizza. He ignores you");
        bookstore =     new Room("in the bookstore. All the shelves are filled with\n" +
                                 "romance novels and the odd textbook");
        pub =           new Room("in the pub. The entirety of the school faculty is\n" +
                                 "here doing jellow shots. Your compsci prof is\n" + 
                                 "passed out. You find your friend in the far corner");
        store =         new Room("in the store. There is blood everywhere and the\n" +
                                 "clerk looks very nervous. You pay no mind");
        courtyard =     new Room("in the courtyard. There is a repair crew here,\n" + 
                                 "they are suntanning. One of them winks at you.\n" + 
                                 "You ponder this");
        garden =        new Room("in the garden. You have always wondered why the\n" +
                                 "university calls a room with a potted furn a garden");
        commons =       new Room("in the learning commons. There is a half-naked\n" +
                                 "woman table dancing here. She has no audience");
        compLab =       new Room("in the computer lab. Several of the computers are\n" +
                                 "displying blue screens with error messages. Two\n" +
                                 "computers seem to have been set on fire");
        adminOffice =   new Room("in the administrative office. The dean is\n" +
                                 "fingerpainting on the walls. He spits at you");
        instOffices =   new Room("in the instructor offices. There is a pack of\n" +
                                 "wild dogs roaming from cubicle to cubicle.\n" +
                                 "They ignore you, they must have eaten");
        corridor =      new Room("in the corridor. There is hornet's nest on the\n" +
                                 "the ceiling. A student is poking at it");
        examRoom =      new Room("in the examination room. You can hear the sounds\n" +
                                 "of people crying");
                
        // initialise room exits & items
        outside.setExit("north", entry);
        outside.createItem("infant", 7.00, 0, true);
        
        entry.setExit("north", garden);
        entry.setExit("south", outside);
        entry.setExit("west", security);
        entry.createItem("fern", 20.0, 0, true);
 
        security.setExit("north", bookstore);
        security.setExit("east", entry);
        security.createItem("identification", 0.05, 0, true);
        
        bookstore.setExit("north", pub);
        bookstore.setExit("south", security);
        bookstore.createItem("newspaper", 0.1, 0, false);
        
        pub.setExit("north", store);
        pub.setExit("south", bookstore);
        pub.setExit("east", garden);
        pub.createItem("money", 0, 50, true);
        pub.createItem("beer", 0.5, 5, true);
        pub.createItem("wine", 0.5, 5, true);
        pub.createItem("asperin", 0.01, 3, true);
        
        store.setExit("south", pub);
        store.setExit("east", courtyard);
        store.createItem("notebook", 2.0, 5.0, true);
        store.createItem("pen", 0.05, 1.0, true);
        
        courtyard.setExit("south", garden);
        courtyard.setExit("west", store);
        courtyard.createItem("lotion", 0.5, 0, true);
        courtyard.createItem("underwear", 0.25, 0, false);
        
        garden.setExit("north", courtyard);
        garden.setExit("south", entry);
        garden.setExit("east", commons);
        garden.setExit("west", pub);
        garden.createItem("dust", 0.001, 0, true);
        
        commons.setExit("north", compLab);
        commons.setExit("south", adminOffice);
        commons.setExit("east", corridor);
        commons.setExit("west", garden);
        commons.createItem("slinky", 1, 0, true);
        
        compLab.setExit("south", commons);
        compLab.createItem("virus", 0, 0, false);
        
        adminOffice.setExit("north", commons);
        adminOffice.setExit("west", instOffices);
        adminOffice.createItem("records", 5.0, 0, true);
        
        instOffices.setExit("east", adminOffice);
        instOffices.createItem("textbook", 2.0, 0, true);
        
        corridor.setExit("north", examRoom);
        corridor.setExit("west", commons);
        corridor.createItem("hope", 0, 0, false);
        
        examRoom.setExit("south", corridor);
        examRoom.setExit("exam", examRoom);

        currentRoom = outside;  // start game outside
    }

    /**
     *  Main play routine.  Loops until end of play.
     */
    public void play() 
    {            
        printWelcome();

        // Enter the main command loop.  Here we repeatedly read commands and
        // execute them until the game is over.
                
        boolean finished = false;
        boolean gameWon = false;
        while(!finished && !gameWon) {
            Command command = parser.getCommand();
            finished = processCommand(command);
            gameWon = gameStatus();
        }
        System.out.println("Thank you for playing. Good bye.");
    }

    /**
     * Print out the opening message for the player.
     */
    private void printWelcome()
    {
        System.out.println();
        System.out.println("You arrive at the entrance to a campus you are not");
        System.out.println("familiar with. You are here to write an exam. You");
        System.out.println("have to find your exam room. You arrive without any");
        System.out.println("pen or pencil, and with nothing write on. So before");
        System.out.println("going to the exam you must find the campus store to");
        System.out.println("purchase these items. You also need a textbook.");
        System.out.println("Your instructor has offered to lend you a textbook,");
        System.out.println("but you don't know where her office is. So you must");
        System.out.println("find your instructor's office and get the text. You");
        System.out.println("must also go to the security office to get your");
        System.out.println("identity card. You cannot enter the exam room");
        System.out.println("without it. You have no money. Your friend has");
        System.out.println("offered to lend you money and will meet you in the");
        System.out.println("pub. To win the game you must enter the exam room");
        System.out.println("and must be carrying all the required items:");
        System.out.println("textbook, notebook, pen or pencil, and identification.");
        System.out.println("Type 'help' if you need help.");
        System.out.println();
        System.out.println(currentRoom.getLongDescription());
        System.out.printf(player.inventoryList());
    }

    /**
     * Given a command, process (that is: execute) the command.
     * @param command The command to be processed.
     * @return true If the command ends the game, false otherwise.
     */
    private boolean processCommand(Command command) 
    {
        boolean wantToQuit = false;

        if(command.isUnknown()) {
            System.out.println("I don't know what you mean...");
            return false;
        }

        String commandWord = command.getCommandWord();
        if(commandWord.equals("help")) {
            printHelp();
        }
        else if(commandWord.equals("go")) {
            goRoom(command);
        }
        else if(commandWord.equals("take")) {
            takeItem(command);
        }
        else if(commandWord.equals("drop")) {
            dropItem(command);
        }
        else if(commandWord.equals("buy")) {
            buyItem(command);
        }
        else if(commandWord.equals("back")) {
            goBack();
        }
        else if(commandWord.equals("quit")) {
            wantToQuit = quit(command);
        }
        // else command not recognised.
        return wantToQuit;
    }

    // implementations of user commands:

    /**
     * Print out some help information.
     * Here we print some stupid, cryptic message and a list of the 
     * command words.
     */
    private void printHelp() 
    {
        System.out.println("You are lost. You are alone. You wander");
        System.out.println("around at the decrepid university.");
        System.out.println();
        System.out.println("Your command words are:");
        parser.showCommands();
    }

    /** 
     * Try to go to one direction. If there is an exit, enter the new
     * room, otherwise print an error message.
     */
    private void goRoom(Command command) 
    {
        if(!command.hasSecondWord()) {
            // if there is no second word, we don't know where to go...
            System.out.println("Go where?");
            return;
        }

        String direction = command.getSecondWord();

        // Try to leave current room.
        Room nextRoom = currentRoom.getExit(direction);

        if(nextRoom == null) {
            System.out.println("There is no door!");
        }
        else {
            roomHistory.add(currentRoom);
            currentRoom = nextRoom;
            System.out.println(currentRoom.getLongDescription());
            System.out.printf(player.inventoryList());
        }
    }
    
    /**
     * Take an item that is contained in the current room.
     */
    private void takeItem(Command command)
    {
        if(!command.hasSecondWord()) {
            // if there is no second word, we don't know what to take.
            System.out.println("Take what?");
            return;
        }

        String itemName = command.getSecondWord();
        
        // Try to take the item
        Item item = currentRoom.takeItem(itemName);

        if(item == null) { // check if the item even exists
            System.out.println("That item does not exist!");
        }
        else if(item.getCost() != 0) {
            // check if the item is money and deposit it to the player's wallet
            if(item.getItemName().equals("money")) {
                player.addMoney(item.getCost());
                System.out.println(currentRoom.getLongDescription());
                System.out.printf(player.inventoryList());
            }
            else {
                System.out.println("If you steal, the management will shoot you.");
                currentRoom.putItem(item); // put the item back into the room
            }
        }
        else if(!item.getCanCarry()) {
            System.out.println("You aren't allowed to have that item!");
            currentRoom.putItem(item); // put the item back into the room
        }
        else {
            if((player.inventoryWeight() + item.getWeightKG()) > MAX_CARRY_KG) {
                System.out.println("That would exceed your carrying capacity.\n" +
                                   "Try dropping something from your inventory first.");
                currentRoom.putItem(item); // put the item back into the room
            }
            else {
                player.takeItem(item);
                System.out.println(currentRoom.getLongDescription());
                System.out.printf(player.inventoryList());
            }
        }
    }
    
    /**
     * Drop an item in the players inventory to the current room.
     */
    private void dropItem(Command command)
    {
        if(!command.hasSecondWord()) {
            // if there is no second word, we don't know what to take.
            System.out.println("Drop what?");
            return;
        }

        String itemName = command.getSecondWord();
        
        // Try to drop the item
        Item item = player.dropItem(itemName);

        if(item == null) { // check if the item even exists
            System.out.println("That item does not exist!");
        }
        else {
            currentRoom.putItem(item);
            System.out.println(currentRoom.getLongDescription());
            System.out.printf(player.inventoryList());
        }
    }
    
    /**
     * Buy an item that costs money.
     */
    private void buyItem(Command command)
    {
        if(!command.hasSecondWord()) {
            // if there is no second word, we don't know what to take.
            System.out.println("Take what?");
            return;
        }

        String itemName = command.getSecondWord();
        
        // Try to take the item
        Item item = currentRoom.takeItem(itemName);

        if(item == null) { // check if the item even exists
            System.out.println("That item does not exist!");
        }
        else if(!item.getCanCarry()) {
            System.out.println("You aren't allowed to have that item!");
            currentRoom.putItem(item); // put the item back into the room
        }
        else {
            if(player.getBalance() < item.getCost()) {
                System.out.println("You don't have enough money for that.");
                currentRoom.putItem(item); // put the item back into the room                
            }
            else if((player.inventoryWeight() + item.getWeightKG()) > MAX_CARRY_KG) {
                System.out.println("That would exceed your carrying capacity." +
                                   "Try dropping something from your inventory first.");
                currentRoom.putItem(item); // put the item back into the room
            }
            else {
                // withdraw the money from the player's wallet
                player.spendMoney(item.getCost());
                // the item has been purchased, remove the associated cost
                item.setCost(0);
                player.takeItem(item);
                System.out.println(currentRoom.getLongDescription());
                System.out.printf(player.inventoryList());
            }
        }    
    }
    
    /**
     * Retrace the user's steps through the rooms.
     */
    private void goBack()
    {
        if(!roomHistory.isEmpty()) {
            // set the current room to the last room in the roomHistory
            // ArrayList and then remove the last entry.
            currentRoom = roomHistory.get(roomHistory.size() - 1);
            roomHistory.remove(roomHistory.size() - 1);

            System.out.println(currentRoom.getLongDescription());
            System.out.printf(player.inventoryList());
        }
        else {
            System.out.println("There is nowhere to return back to!");
        }
    }

    /**
     * Check whether the player has won the game and display an
     * appropriate message for this case.
     * @return true if the game has been won.
     */
    private boolean gameStatus()
    {
        // check whether the current room is the exam room
        // as well as whether the player has all the items
        if(currentRoom.getExit("exam") != null && player.allRequiredItems()) {
            System.out.println();
            System.out.println("You have succeeded in bringing all the items needed");
            System.out.println("to write your exam! You promptly pass out. All is black.");
            System.out.println();
        
            return true;
        }
        else {
            return false;
        }
    }
    
    /** 
     * "Quit" was entered. Check the rest of the command to see
     * whether we really quit the game.
     * @return true, if this command quits the game, false otherwise.
     */
    private boolean quit(Command command) 
    {
        if(command.hasSecondWord()) {
            System.out.println("Quit what?");
            return false;
        }
        else {
            return true;  // signal that we want to quit
        }
    }
}