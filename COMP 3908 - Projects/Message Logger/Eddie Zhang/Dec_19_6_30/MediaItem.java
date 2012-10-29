/*
 * AbstractMediaItem.java
 *
 * © <your company here>, 2003-2008
 * Confidential and proprietary.
 */
package src;
import net.rim.device.api.io.Base64OutputStream;
import java.io.IOException;

/**
 * 
 */
abstract class MediaItem {
    
    protected String format;
    protected byte data[];
    protected String type;
    
    public MediaItem(byte[] data, String format, String type) {
        this.data = data;
        this.format = format;
        this.type = type;
    }
    
    public void delete() {}
    
    public String type() {
        return this.type();
    }
    
    public String format() {
        return this.format;
    }
    
    public byte[] toBase64() {
        try {
            return Base64OutputStream.encode(this.data, 0, this.data.length, false, false);
        } catch (IOException e) {
            return "Bad Data!".getBytes();
        }
    }
} 
