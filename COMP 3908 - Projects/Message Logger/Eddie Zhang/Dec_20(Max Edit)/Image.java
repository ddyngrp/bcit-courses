/*
 * Image.java
 *
 * MLogger, 2008
 * Confidential and proprietary.
 */
 package src;
 import net.rim.device.api.io.Base64OutputStream;

class Image extends MediaItem {
    
    /**
     * Image Constructor
     * @param data The image as a byte array.
     * @param format The format of the image (jpg, bmp, etc).
     */
    Image(byte[] data, String format) {
        super(data, format, "image");
    }
    
} 
