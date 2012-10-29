import javax.swing.JComponent;
import javax.swing.BorderFactory;
import java.awt.BasicStroke;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Insets;
import java.awt.Color;
import java.awt.geom.Line2D;

/* XMarksTheSpot is used by ComponentDisplayer. */
public class XMarksTheSpot extends JComponent {
    Dimension preferredSize = null;
    
    public XMarksTheSpot() {
        setOpaque(true);
        
        //Set the border using either a MatteBorder (standard, used in 
        //Exercise 1) or a StripeBorder (custom, used in Exercise 3).
        //You can find the exercises here:
        //  http://java.sun.com/docs/books/tutorial/uiswing/QandE/questions-ch6.html
        setBorder(BorderFactory.createMatteBorder(5,5,5,5, Color.BLACK));
        //setBorder(new StripeBorder());
    }
    
    protected void paintComponent(Graphics g) {
        if (isOpaque()) {
            g.setColor(getBackground());
            g.fillRect(0,0,getWidth(),getHeight());
            g.setColor(getForeground());
        }
            
        Graphics2D g2 = (Graphics2D)g;
        Insets insets = getInsets();
        g2.setStroke(new BasicStroke(5.0f));
        g2.draw(new Line2D.Double(insets.left,
                                  insets.top,
                                  getWidth() - insets.right,
                                  getHeight() - insets.bottom));
        g2.draw(new Line2D.Double(insets.left,
                                  getHeight() - insets.bottom,
                                  getWidth() - insets.right,
                                  insets.top));
    }
    
    public Dimension getPreferredSize() {
        if (preferredSize == null) {
            return new Dimension(250,100); 
        } else {
            return super.getPreferredSize();
        }
    }
    
    public void setPreferredSize(Dimension newPrefSize) {
        preferredSize = newPrefSize;
        super.setPreferredSize(newPrefSize);
    }
}
