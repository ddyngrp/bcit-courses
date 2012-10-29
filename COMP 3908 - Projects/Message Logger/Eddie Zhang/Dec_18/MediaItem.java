/**
 * @author doug
 *
 */
package src;
public interface MediaItem {
    
    /**
     * Deletes the media.
     */
    public void delete();
    
    /**
     * Identifies the media item type (as a string)
     * @return Media Item Type.
     */
    public String type();
    
    /**
     */
    public String toBase64();
} 

