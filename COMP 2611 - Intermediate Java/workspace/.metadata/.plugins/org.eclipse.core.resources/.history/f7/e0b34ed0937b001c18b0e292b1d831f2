import javax.swing.ImageIcon;

/*
 * This class is used by IconDemoApplet.java
 */

public class Photo {
    public String filename;
    public String caption;
    public int width;
    public int height;
    public ImageIcon icon;

    public Photo(String filename, String caption, int w, int h) {
        this.filename = filename;
        if (caption == null)
            this.caption = filename;
        else
            this.caption = caption;
        width = w;
        height = h;
        icon = null;
    }

    public void setIcon(ImageIcon i) {
        icon = i;
    }

    public ImageIcon getIcon() {
        return icon;
    }
}
