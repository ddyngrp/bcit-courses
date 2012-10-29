/*
 * MediaNode.java
 *
 * © <your company here>, 2003-2008
 * Confidential and proprietary.
 */


/**
 * 
 */
class MediaNode {
    
    private MediaNode prev;
    private MediaNode next;
    private MediaItem item;
    
    MediaNode(MediaNode prev, MediaItem item, MediaNode next) {
        this.prev = prev;
        this.item = item;
        this.next = next;
    }
    
    MediaNode(MediaItem item) {
        this.prev = null;
        this.item = item;
        this.next = null;
    }
    
    public void prev(MediaNode prev) {
        this.prev = prev;
    }
    
    public void next(MediaNode next) {
        this.next = next;
    }
    
    public MediaNode prev() {
        return this.prev;
    }
    
    public MediaNode next() {
        return this.next;
    }
    
    public MediaItem item() {
        return this.item;
    }
    
    public void delete() {
        if (this.prev != null)
            this.prev.next(this.next);
        if (this.next != null)
            this.next.prev(this.prev);
        this.item.delete();
    }
    
} 
