/*
 * Video.java
 *
 * MLogger, 2008
 * Confidential and proprietary.
 */
package src;
import net.rim.device.api.ui.component.Status;
class Video implements MediaItem {
    public Video() {
        // TODO: Call Max's Code Here!
        Status.show("Not Implemented yet");
    }
    
    public void delete() {
    }
    
    public String type() {
        return "video";
    }
    
    public String toBase64() {
        return "Video as Base64";
    }
} 
