/*
 * TrackFocusDemo.java is a 1.4 example that
 * requires the following files:
 *     Picture.java
 *     images/Maya.jpg
 *     images/Anya.jpg
 *     images/Laine.jpg
 *     images/Cosmo.jpg
 *     images/Adele.jpg
 *     images/Alexi.jpg
 */
import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JLabel;

import java.beans.*; //Property change stuff
import java.awt.*;
import java.awt.event.*;

public class TrackFocusDemo extends JPanel {

    Picture pic1, pic2, pic3, pic4, pic5, pic6;
    JLabel info;
    static String mayaString = "Maya";
    static String anyaString = "Anya";
    static String laineString = "Laine";
    static String cosmoString = "Cosmo";
    static String adeleString = "Adele";
    static String alexiString = "Alexi";
    String[] comments = { "Oops. What is this?",
                          "This is Maya",
                          "This is Anya",
                          "This is Laine",
                          "This is Cosmo",
                          "This is Adele",
                          "This is Alexi" };

    public TrackFocusDemo() {
        super(new BorderLayout());

        JPanel mugshots = new JPanel(new GridLayout(2,3));
        pic1 = new Picture(createImageIcon("images/" +
                    mayaString + ".jpg", mayaString).getImage());
        pic1.setName("1");
        mugshots.add(pic1);
        pic2 = new Picture(createImageIcon("images/" +
                    anyaString + ".jpg", anyaString).getImage());
        pic2.setName("2");
        mugshots.add(pic2);
        pic3 = new Picture(createImageIcon("images/" +
                    laineString + ".jpg", laineString).getImage());
        pic3.setName("3");
        mugshots.add(pic3);
        pic4 = new Picture(createImageIcon("images/" +
                    cosmoString + ".jpg", cosmoString).getImage());
        pic4.setName("4");
        mugshots.add(pic4);
        pic5 = new Picture(createImageIcon("images/" +
                    adeleString + ".jpg", adeleString).getImage());
        pic5.setName("5");
        mugshots.add(pic5);
        pic6 = new Picture(createImageIcon("images/" +
                    alexiString + ".jpg", alexiString).getImage());
        pic6.setName("6");
        mugshots.add(pic6);

        info = new JLabel("Nothing selected");

        setPreferredSize(new Dimension(450, 350));
        add(mugshots, BorderLayout.CENTER);
        add(info, BorderLayout.PAGE_END);
        setBorder(BorderFactory.createEmptyBorder(20,20,20,20));

        KeyboardFocusManager focusManager =
            KeyboardFocusManager.getCurrentKeyboardFocusManager();
        focusManager.addPropertyChangeListener(
            new PropertyChangeListener() {
                public void propertyChange(PropertyChangeEvent e) {
                    String prop = e.getPropertyName();
                    if (("focusOwner".equals(prop)) &&
                          (e.getNewValue() != null) &&
                          ((e.getNewValue()) instanceof Picture)) {

                        Component comp = (Component)e.getNewValue();
                        String name = comp.getName();
                        Integer num = new Integer(name);
                        int index = num.intValue();
                        if (index < 0 || index > comments.length) {
                            index = 0;
                        }
                        info.setText(comments[index]);
                    }
                }
            }
        );
    }

    /** Returns an ImageIcon, or null if the path was invalid. */
    protected static ImageIcon createImageIcon(String path,
                                               String description) {
        java.net.URL imageURL = TrackFocusDemo.class.getResource(path);

        if (imageURL == null) {
            System.err.println("Resource not found: "
                               + path);
            return null;
        } else {
            return new ImageIcon(imageURL, description);
        }
    }

    /**
     * Create the GUI and show it.  For thread safety,
     * this method should be invoked from the
     * event-dispatching thread.
     */
    private static void createAndShowGUI() {
        //Make sure we have nice window decorations.
        JFrame.setDefaultLookAndFeelDecorated(true);

        //Create and set up the window.
        JFrame frame = new JFrame("TrackFocusDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        JComponent newContentPane = new TrackFocusDemo();
        newContentPane.setOpaque(true); //content panes must be opaque
        frame.setContentPane(newContentPane);

        //Display the window.
        frame.pack();
        frame.setVisible(true);
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
