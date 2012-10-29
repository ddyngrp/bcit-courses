import java.awt.GridLayout;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JFrame;
import javax.swing.ImageIcon;

/*
 * LabelDemo.java is a 1.4 application that needs one other file:
 *   images/middle.gif
 */
public class LabelDemo extends JPanel {
    public LabelDemo() {
        super(new GridLayout(3,1));  //3 rows, 1 column
        JLabel label1, label2, label3;

        ImageIcon icon = createImageIcon("images/middle.gif",
                                         "a pretty but meaningless splat");

        //Create the first label.
        label1 = new JLabel("Image and Text",
                            icon,
                            JLabel.CENTER);
        //Set the position of its text, relative to its icon:
        label1.setVerticalTextPosition(JLabel.BOTTOM);
        label1.setHorizontalTextPosition(JLabel.CENTER);

        //Create the other labels.
        label2 = new JLabel("Text-Only Label");
        label3 = new JLabel(icon);

        //Create tool tips, for the heck of it.
        label1.setToolTipText("A label containing both image and text");
        label2.setToolTipText("A label containing only text");
        label3.setToolTipText("A label containing only an image");

        //Add the labels.
        add(label1);
        add(label2);
        add(label3);
    }

    /** Returns an ImageIcon, or null if the path was invalid. */
    protected static ImageIcon createImageIcon(String path,
                                               String description) {
        java.net.URL imgURL = LabelDemo.class.getResource(path);
        if (imgURL != null) {
            return new ImageIcon(imgURL, description);
        } else {
            System.err.println("Couldn't find file: " + path);
            return null;
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
        JFrame frame = new JFrame("LabelDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        LabelDemo newContentPane = new LabelDemo();
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
