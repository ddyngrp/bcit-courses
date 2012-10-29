/*
 * Sounds.java
 *
 * MLogger, 2008
 * Confidential and proprietary.
 */
package src;
class Sound extends MediaItem {
    
    /**
     * Sound Constructor
     * @param data The sound as a byte array.
     * @param format The format of the sound (wav, wma, etc).
     */
    Sound(byte[] data, String format) {
        super(data, format, "sound");
    }
    
}
