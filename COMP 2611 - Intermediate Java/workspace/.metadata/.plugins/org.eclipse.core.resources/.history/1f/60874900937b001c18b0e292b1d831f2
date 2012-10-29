import javax.swing.Icon;
import java.awt.Color;
import java.awt.Component;
import java.awt.Graphics;

/* 
 * XMarksTheSpot is used by the ButtonDemo version used by the  
 * answer to exercise 2 of the Performing Custom Painting lesson:
 * http://java.sun.com/docs/books/tutorial/uiswing/QandE/questions-ch6.html
 */
public class SquareIcon implements Icon {
    private static final int SIZE = 10;
        
    public void paintIcon(Component c, Graphics g,
                          int x, int y) {
        if (c.isEnabled()) {
            g.setColor(Color.RED);
        } else {
            g.setColor(Color.GRAY);
        }
        
        g.fillRect(x, y, SIZE, SIZE);
    }
    
    public int getIconWidth() {
        return SIZE;
    }
    
    public int getIconHeight() {
        return SIZE;
    }
}
