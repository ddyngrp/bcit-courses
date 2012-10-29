/*
 * MediaItem.java
 *
 * MLogger, 2008
 * Confidential and proprietary.
 */
 package src;
import net.rim.device.api.io.Base64OutputStream;
import java.io.IOException;

/**
 * 
 */
abstract class MediaItem {
    
    /**
     * Media Format (png, bmp, wmv, etc)
     */
    protected String format;
    
    /**
     * Actual media as a byte array.
     */
    protected byte data[];
    
    /**
     * Type of media (image, video, etc)
     */
    protected String type;
    
    /**
     * Constructor.
     * @param data The media itself as a byte array.
     * @param format The format of the media.
     * @param type The type of media (usually defined by the subclass)
     */
    public MediaItem(byte[] data, String format, String type) {
        this.data = data;
        this.format = format;
        this.type = type;
    }
    
    /**
     * Deletes the media (never really used, just in case).
     */
    public void delete() {}
    
    /**
     * Returns the type of media.
     * @return The type of media.
     */
    public String type() {
        return this.type;
    }
    
    /**
     * Returns the format of the media.
     * @return The format of the media.
     */
    public String format() {
        return this.format;
    }
    
    /**
     * Converts the media data to base64 format (for SOAP:XML inclusion).
     * @return The media as a base64 byte array.
     */
    public String toBase64() {
        try {
            return new String(Base64OutputStream.encode(this.data, 0, this.data.length, false, false));
        } catch (IOException e) {
            return "Bad Data!";
        }
    }
} 
