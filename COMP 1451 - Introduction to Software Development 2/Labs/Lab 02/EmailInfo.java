import java.util.HashMap;
import java.util.Set;

/**
 * This class stores names and email addresses.
 * 
 * @author Steffen L. Norgren 
 * @version 1.0 (13.July.2007)
 */
public class EmailInfo
{
    private HashMap <String, String> emailInfo;
    //private HashSet <String> emailSet;

    /**
     * Initializes the emailInfo hashmap, but doesn't do anything
     * else of interest or consequence.
     */
    public EmailInfo()
    {
        emailInfo = new HashMap<String, String>();
    }
    
    /**
     * Add a friend to the emailInfo HashMap
     * 
     * @param friendName The person's full name
     * @param friendEmail The person's full email address
     */
    public void addFriend( String friendName, String friendEmail )
    {
        emailInfo.put( friendName.toUpperCase(), friendEmail );
    }
    
    /**
     * Remove a friend from the emailInfo HashMap
     * 
     * @param friendName The person's name to delete
     */
    public void removeFriend( String friendName )
    {
        emailInfo.remove( friendName.toUpperCase() );
    }
    
    /**
     * Return the email address of a friend in the HashMap
     * 
     * @param friendName The person's name of whom's email to return
     */
    public String returnEmail( String friendName )
    {
        return emailInfo.get( friendName.toUpperCase() );
    }
    

    /**
     * Display all friends and their email address within the HashMap
     */
    public void listAllFriends()
    {
        Set<String> allFriends = emailInfo.keySet();
        
        for ( String name : allFriends )
        {            
            System.out.println( name + " " + returnEmail(name) );
        }
    }
}
