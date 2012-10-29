/*
 * MediaList.java
 *
 * MLogger, 2008
 * Confidential and proprietary.
 */
package src; 
class MediaList {
    /**
     * First media item in the list (null if empty).
     */
    private MediaNode first = null;
    private MediaNode last = null;
    private int size = 0;
    
    MediaList() {}
    
    public void add(MediaItem item) {
        MediaNode node = new MediaNode(this.last, item, null);
        if (first == null)
            first = node;
        if (this.last != null)
            this.last.next(node);
        this.last = node;
        this.size++;
    }
    
    public void delete(int index) {
        if (this.size > 0) {
            MediaNode node = this.first;
            for (int i =0; i <= index && node != null; ++i) {
                node = node.next();
            }
            if (node != null) {
                node.delete();
                this.size--;
            }
        }
    }
    
    public MediaItem get(int index) {
        MediaNode node = this.first;
        for (int i=0; i <= index && node != null; ++i) {
            node = node.next();
        }
        return (node == null) ? null : node.item();
    }
    
    public MediaNode iterator() {
        return this.first;
    }
    
    public int size() {
        return this.size;
    }
    
    public void clear() {
        for (; this.size > 0; this.size--)
            this.first.delete();
        this.first = null;
        this.last = null;
    }
} 
