/*
 * Image.java
 *
 * MLogger, 2008
 * Confidential and proprietary.
 */
 
 import net.rim.device.api.io.Base64OutputStream;
 
class Image extends MediaItem {
    
    Image(byte[] data, String format) {
        super(data, format, "image");
    }
    
} 
