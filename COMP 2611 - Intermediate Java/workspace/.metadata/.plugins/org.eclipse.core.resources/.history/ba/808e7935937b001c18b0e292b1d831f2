import javax.swing.border.Border;
import java.awt.Color;
import java.awt.Component;
import java.awt.Graphics;
import java.awt.Insets;

/* StripeBorder is used by XMarksTheSpot. */
public class StripeBorder implements Border {
    private static final int HEIGHT = 15;
        
    public void paintBorder(Component c, Graphics g,
                            int x, int y,
                            int width, int height) {
        g.setColor(Color.RED);
        
        g.fillRect(x, y, c.getWidth(), HEIGHT);
    }
    
    public Insets getBorderInsets(Component c) {
        return new Insets(HEIGHT, 0, 0, 0);
    }
    
    public boolean isBorderOpaque() {
        return true;
    }
}
