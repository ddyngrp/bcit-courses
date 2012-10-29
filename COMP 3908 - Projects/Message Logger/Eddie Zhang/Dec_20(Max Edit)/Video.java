/*
 * Video.java
 *
 * MLogger, 2008
 * Confidential and proprietary.
 */
package src;
class Video extends MediaItem {
    
    /**
     * Video Constructor
     * @param data The video as a byte array.
     * @param format The format of the video (wmv, mpeg, etc).
     */
    Video(byte[] data, String format) {
        super(data, format, "video");
    }
}
