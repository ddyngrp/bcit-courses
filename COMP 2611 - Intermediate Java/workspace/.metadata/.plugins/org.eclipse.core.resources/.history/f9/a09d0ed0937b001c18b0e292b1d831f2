import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

/*
 * AccessibleScrollDemo requires these files:
 *    Rule.java
 *    Corner.java
 *    ScrollablePicture.java
 *    images/youngdad.jpeg
 */
public class AccessibleScrollDemo extends JPanel 
                                  implements ItemListener {
    private Rule columnView;
    private Rule rowView;

    private JToggleButton isMetric;
    private ScrollablePicture picture;

    public AccessibleScrollDemo() {
        // Get the image to use.
        ImageIcon david = createImageIcon("images/youngdad.jpeg",
                          "Photograph of David McNabb in his youth.");

        // Create the row and column headers.
        columnView = new Rule(Rule.HORIZONTAL, true);
        if (david != null) {
            columnView.setPreferredWidth(david.getIconWidth());
        } else {
            columnView.setPreferredWidth(320);
        }
        columnView.getAccessibleContext().setAccessibleName("Column Header");
        columnView.getAccessibleContext().
                setAccessibleDescription("Displays horizontal ruler for " +
                                         "measuring scroll pane client.");
        rowView = new Rule(Rule.VERTICAL, true);
        if (david != null) {
            rowView.setPreferredHeight(david.getIconHeight());
        } else {
            rowView.setPreferredHeight(480);
        }
        rowView.getAccessibleContext().setAccessibleName("Row Header");
        rowView.getAccessibleContext().
                setAccessibleDescription("Displays vertical ruler for " +
                                         "measuring scroll pane client.");

        // Create the corners.
        JPanel buttonCorner = new JPanel();
        isMetric = new JToggleButton("cm", true);
        isMetric.setFont(new Font("SansSerif", Font.PLAIN, 11));
        isMetric.setMargin(new Insets(2,2,2,2));
        isMetric.addItemListener(this);
        isMetric.setToolTipText("Toggles rulers' unit of measure " +
                                "between inches and centimeters.");
        buttonCorner.add(isMetric); //Use the default FlowLayout
        buttonCorner.getAccessibleContext().
                     setAccessibleName("Upper Left Corner");

        String desc = "Fills the corner of a scroll pane " +
                      "with color for aesthetic reasons.";
        Corner lowerLeft = new Corner();
        lowerLeft.getAccessibleContext().
                  setAccessibleName("Lower Left Corner");
        lowerLeft.getAccessibleContext().setAccessibleDescription(desc);

        Corner upperRight = new Corner();
        upperRight.getAccessibleContext().
                   setAccessibleName("Upper Right Corner");
        upperRight.getAccessibleContext().setAccessibleDescription(desc);
        
        // Set up the scroll pane.
        picture = new ScrollablePicture(david,
                                        columnView.getIncrement());
        picture.setToolTipText(david.getDescription());
        picture.getAccessibleContext().setAccessibleName(
                                         "Scroll pane client");

        JScrollPane pictureScrollPane = new JScrollPane(picture);
        pictureScrollPane.setPreferredSize(new Dimension(300, 250));
        pictureScrollPane.setViewportBorder(
                BorderFactory.createLineBorder(Color.black));

        pictureScrollPane.setColumnHeaderView(columnView);
        pictureScrollPane.setRowHeaderView(rowView);

        // In theory, to support internationalization you would change
        // UPPER_LEFT_CORNER to UPPER_LEADING_CORNER,
        // LOWER_LEFT_CORNER to LOWER_LEADING_CORNER, and
        // UPPER_RIGHT_CORNER to UPPER_TRAILING_CORNER.  In practice,
        // bug #4467063 makes that impossible (at least in 1.4.0).
        pictureScrollPane.setCorner(JScrollPane.UPPER_LEFT_CORNER,
                                    buttonCorner);
        pictureScrollPane.setCorner(JScrollPane.LOWER_LEFT_CORNER,
                                    lowerLeft);
        pictureScrollPane.setCorner(JScrollPane.UPPER_RIGHT_CORNER,
                                    upperRight);

        // Put it in this panel.
        setLayout(new BoxLayout(this, BoxLayout.X_AXIS));
        add(pictureScrollPane);
        setBorder(BorderFactory.createEmptyBorder(20,20,20,20));
    }

    public void itemStateChanged(ItemEvent e) {
        if (e.getStateChange() == ItemEvent.SELECTED) {
            // Turn it to metric.
            rowView.setIsMetric(true);
            columnView.setIsMetric(true);
        } else {
            // Turn it to inches.
            rowView.setIsMetric(false);
            columnView.setIsMetric(false);
        }
        picture.setMaxUnitIncrement(rowView.getIncrement());
    }

    /** Returns an ImageIcon, or null if the path was invalid. */
    protected static ImageIcon createImageIcon(String path,
                                               String description) {
        java.net.URL imgURL = AccessibleScrollDemo.class.getResource(path);
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
        JFrame frame = new JFrame("AccessibleScrollDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        JComponent newContentPane = new AccessibleScrollDemo();
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
