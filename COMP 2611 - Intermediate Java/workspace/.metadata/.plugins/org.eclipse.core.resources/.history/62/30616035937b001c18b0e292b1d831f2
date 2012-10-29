import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import java.awt.Color;
import java.awt.Component;

public class Layout3 {
    /**
     * Create the GUI and show it.  For thread safety,
     * this method should be invoked from the
     * event-dispatching thread.
     */
    private static void createAndShowGUI() {
        //Make sure we have nice window decorations.
        JFrame.setDefaultLookAndFeelDecorated(true);

        //Create and set up the window.
        JFrame frame = new JFrame("Layout3");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Add the innards.
        JPanel p = new JPanel();
        p.setLayout(new BoxLayout(p, BoxLayout.PAGE_AXIS));
        p.add(createComponent("Component 1"));
        p.add(Box.createVerticalGlue());
        p.add(createComponent("Component 2"));
        p.add(createComponent("Component 3"));
        p.add(createComponent("Component 4"));
        frame.setContentPane(p);

        //Display the window.
        frame.pack();
        frame.setVisible(true);
    }

    private static JComponent createComponent(String s) {
        JLabel l = new JLabel(s);
        l.setBorder(BorderFactory.createMatteBorder(5,5,5,5,
                                                    Color.DARK_GRAY));
        l.setHorizontalAlignment(JLabel.CENTER);
        l.setAlignmentX(Component.CENTER_ALIGNMENT); //use middle of row
        return l;
    }

    public static void main(String[] args) {
        //Schedule a job for the event-dispatching thread:
        //creating and showing this application's GUI.
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                createAndShowGUI();
            }
        });
    }
}