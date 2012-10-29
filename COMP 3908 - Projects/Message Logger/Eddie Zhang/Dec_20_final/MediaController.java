/*
 * MediaController.java
 *
 * MLogger, 2008
 * Confidential and proprietary.
 */
 package src;
public class MediaController {
    
    /**
     * Set to true whenever something is modified, then false when checked.
     */
    private boolean updated = true;
    
    /**
     * List of recorded media items.
     */
    private MediaList media = new MediaList();
    
    /**
     * Title of the memo.
     */
    private String title = "";
    
    /**
     * Description of the memo (body).
     */
    private String description = "";
    
    /**
     * SessionID used to send the memos to the server.
     */
    private int sessionID = 0;
    
    /**
     * Returns the sessionID.
     * @return The sessionID.
     */
    public int sessionID() {
        return this.sessionID;
    }
    
    /**
     * Sets the sessionID.
     * @param sessionID The sessionID to set.
     */
    public void sessionID(int sessionID) {
        this.sessionID = sessionID;
    }
    
    /**
     * Sets the memo's title.
     * @param txt The string to set the memo to.
     */
    public void title(String txt) {
        this.updated = true;
        this.title = txt;
    }
    
    /**
     * Sets the memo's description.
     * @param txt The string to set the memo to.
     */
    public void description(String txt) {
        this.updated = true;
        this.description = txt;
    }

    /**
     * Returns the memo's title.
     * @return The memo's title.
     */
    public String title() {
        this.updated = true;
        return this.title;
    }
    
    /**
     * Returns the memod's description.
     * @return The memo's description.
     */
    public String description() {
        return this.description;
    }
    
    /**
     * Adds a media item to the list.
     * @param item MediaItem to add.
     */
    public void add(MediaItem item) {
        this.updated = true;
        this.media.add(item);
    }
    
    /**
     * Returns a specified MediaItem.
     * @param i The indeo of the MediaItem to return.
     * @return The MediaItem at index i (or null if invalid index).
     */
    public MediaItem get(int i) {
        return (Video)this.media.get(i);
    }
    
    /**
     * Returns an iterator.
     * @return An Iterator
     */
    public MediaNode iterator() {
        return this.media.iterator();
    }
    
    /**
     * Deletes a media item (does nothing if index is invalid).
     * @param index The index of the media item to delete.
     */
    public void delete(int index) {
        this.media.delete(index);
    }
    
    /**
     * Resets the class.
     * <ul>
     *    <li>Title (set to "")</li>
     *    <li>Description (set to "")</li>
     *    <li>All Media Items (deleted)</li>
     * </ul>
     */
    public void reset() {
        this.updated = true;
        this.title = "";
        this.description = "";
        this.media.clear();
    }
    
    /**
     * Return number of MediaItems. 
     * @return number of MediaItems.
     */
    public int numItems() {
        return this.media.size();
    }
    
    /**
     * Counts the number of media items of a given type.
     * @param type Type of media to count.
     * @return Number of that type of mediai recorded.
     */
    public int count(String type) {
        int c=0;
        for (MediaNode it = this.media.iterator(); it != null; it = it.next()) {
            if (it.item().type().equals(type))
                c++;
        }
        return c;
    }
    
    public boolean loggedIn() {
        return this.sessionID > 0;
    }
    
    /**
     * Returns true if the class has been modified since last checked.
     * @return true if modified, else false.
     */
    public boolean updated() {
        boolean retVal = this.updated;
        this.updated = false;
        return retVal;
    }
    
    // TODO: Remove!
    public void fake() {
        this.title = "Memo Title";
        this.description = "Memo Description";
        this.add(new Image(new String("ABC").getBytes(), "png-image"));
        //this.add(new Video(new String("DEF").getBytes(), "wmv-video"));
        //this.add(new Sound(new String("GHI").getBytes(), "wav-sound"));
        //this.add(new Image(new String("JKL").getBytes(), "png-image"));
        //this.add(new Sound(new String("MNO").getBytes(), "wav-sound"));
        //this.add(new Image(new String("PQR").getBytes(), "png-image"));
    }
} 

