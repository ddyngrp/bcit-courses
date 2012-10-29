import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.BorderLayout;

/* 
 * ComponentDisplayer.java is a 1.4 application that requires the following files:
 *   XMarksTheSpot.java
 */
//Note: This program doesn't create its GUI in invokeAndWait.  Since it does
//no event handling, that's almost certainly OK.
public class ComponentDisplayer {
    public static void main(String[] args) {
        JFrame.setDefaultLookAndFeelDecorated(true);
        JFrame f = new JFrame("ComponentDisplayer");
        
        JPanel p = new JPanel(new BorderLayout());
        p.add(new XMarksTheSpot(), BorderLayout.CENTER);

        f.setContentPane(p);
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.pack();
        f.setVisible(true);
    }
}