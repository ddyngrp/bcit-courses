import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;
import java.util.HashMap;
import java.util.Set;
import java.util.StringTokenizer;
import java.util.Scanner;
import java.util.Arrays;

/**
 * A simple model of a mail server. The server is able to receive
 * mail items for storage, and deliver them to clients on demand.
 * 
 * @author David J. Barnes, Michael Kolling, Steffen L. Norgren
 * @version 2007.07.24
 */
public class MailServer
{
    // The keys to the HashMap are be the names of the recipients, 
    // each value is be an ArrayList containing all the MailItems
    // stored for that recipient.
    private HashMap<String, ArrayList<MailItem>> allMail;
    // static array containing all spam words
    private static final String[] spamWords = {"SPAM", "cheap drugs", "deal for you",
                                               "loan request", "hot news"};

    /**
     * Construct a mail server.
     */
    public MailServer()
    {
        allMail = new HashMap<String, ArrayList<MailItem>>();
    }

    /**
     * Return how many mail items are waiting for a user.
     * @param who The user to check for.
     * @return How many items are waiting.
     */
    public int howManyMailItems(String who)
    {
        who = firstToUpper(who); // Make sure the format is correct
        
        // retrieve the arraylist for a particular user
        ArrayList<MailItem> mailItems = allMail.get(who);
        
        int count = 0;
        if(mailItems != null) { // avoid a null pointer exception
            for(MailItem mail : mailItems) {
                count++;
            }
        }
        return count;
    }

    /**
     * Return the next mail item for a user or null if there
     * are none.
     * @param who The user requesting their next item.
     * @return The user's next item.
     */
    public MailItem getNextMailItem(String who)
    {
        who = firstToUpper(who); // Make sure the format is correct

        // retrieve the arraylist for a particular user
        ArrayList<MailItem> mailItems = allMail.get(who);
        
        if(mailItems != null) {
            Iterator<MailItem> it = mailItems.iterator();
            while(it.hasNext()) {
                MailItem item = it.next();
                it.remove();
                return item;
            }
        }
        return null;
    }

    /**
     * Add the given mail item to the message list.
     * @param item The mail item to be stored on the server.
     */
    public void post(MailItem item)
    {
        // retrieve the arraylist for a particular user
        ArrayList<MailItem> mailItems = allMail.get(firstToUpper(item.getTo()));
        
        if(mailItems == null) { // if the arraylist is null, create one
            mailItems = new ArrayList<MailItem>();
            allMail.put(firstToUpper(item.getTo()), mailItems);
        }
        
        if(!spamChecker(item.getSubject())) {
            mailItems.add(item);
        }
    }
    
    /**
     * Return true of the string contains any of the words
     * within the spamWords array.
     * 
     * @param string a string of any given length
     * @return true or false if the string contains a spamWord
     */
    public boolean spamChecker(String string)
    {
        for(int i = 0; i < spamWords.length; i++ ) {
            if(string.toLowerCase().contains(spamWords[i].toLowerCase())) {
                if(spamWords[i].equals("SPAM")) { // exception for starting with SPAM
                    if(string.toLowerCase().startsWith(spamWords[i].toLowerCase())) {
                        return true;
                    }
                }
                else {
                    return true;
                }
            }
        }
        return false;
    }
    
    /**
     * Iterates through all the users, prints out each user name, and 
     * prints out all the emails associated with that user.
     */
    public void printAllMessages()
    {
        Set<String> allUsers = allMail.keySet();
        
        for(String name : allUsers) { // iterate through the users
            // retrieve the arraylist for a particular user
            ArrayList<MailItem> mailItems = allMail.get(firstToUpper(name));
            
            if(mailItems != null) { // check if there is any mail
                System.out.println("==============< All mail for " + name +
                                  " >==============");
                
                for(MailItem mail : mailItems) { // iterate through the mail
                    System.out.println("To: " + firstToUpper(mail.getTo()));
                    System.out.println("From: " + firstToUpper(mail.getFrom()));
                    System.out.println("Subject: " + mail.getSubject());
                    System.out.println("Message: " + mail.getMessage());
                    System.out.println("-------------------------------------------");
                }
            }
            else {
                System.out.println("No mail for " + name);
            }
        }
    }
    
    /**
     * Convert the first letter in any string to uppercase
     * as well as the first letter after any space.
     * 
     * @param string a string of any given length
     * @return the converted string
     */
    public String firstToUpper(String string)
    {
        String inputString = null;
        String workingString = null;
        
        // Find all words on a line
        Scanner tokenizer = new Scanner(string);
        if(tokenizer.hasNext()) {
            inputString = tokenizer.next();
            workingString = inputString.substring(0,1).toUpperCase()
                            + inputString.substring(1);
                            
            while(tokenizer.hasNext()) {
                inputString = tokenizer.next();
                workingString += " " + inputString.substring(0,1).toUpperCase()
                                + inputString.substring(1);
            }
        }
        
        return workingString;
    }
}
