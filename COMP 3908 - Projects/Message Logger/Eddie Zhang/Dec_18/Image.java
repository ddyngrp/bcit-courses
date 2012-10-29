/*
 * Image.java
 *
 * MLogger, 2008
 * Confidential and proprietary.
 */
 package src;
class Image implements MediaItem {
    public Image() {
        // TODO: Call Max's Code Here!
        CameraStream cs = new CameraStream();
    }
    
    public void delete() {
    }
    
    public String type() {
        return "image";
    }
    
    public String toBase64() {
        return "Image as Base64";
    }
} 
