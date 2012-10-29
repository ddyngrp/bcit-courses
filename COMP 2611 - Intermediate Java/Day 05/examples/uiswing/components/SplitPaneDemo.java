import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

import java.util.*;

//SplitPaneDemo itself is not a visible component.
public class SplitPaneDemo implements ListSelectionListener {
    private Vector imageNames;
    private JLabel picture;
    private JList list;
    private JSplitPane splitPane;

    public SplitPaneDemo() {
        //Read image names from a properties file.
        ResourceBundle imageResource;
        try {
            imageResource = ResourceBundle.getBundle("imagenames");
            String imageNamesString = imageResource.getString("images");
            imageNames = parseList(imageNamesString);
        } catch (MissingResourceException e) {
            handleMissingResource(e);
        }

        //Create the list of images and put it in a scroll pane.
        list = new JList(imageNames);
        list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        list.setSelectedIndex(0);
        list.addListSelectionListener(this);
        JScrollPane listScrollPane = new JScrollPane(list);

        //Set up the picture label and put it in a scroll pane.
        ImageIcon firstImage = createImageIcon("images/" +
                                     (String)imageNames.firstElement());
        if (firstImage != null) {
            picture = new JLabel(firstImage);
        } else {
            picture = new JLabel((String)imageNames.firstElement());
        }
        JScrollPane pictureScrollPane = new JScrollPane(picture);

        //Create a split pane with the two scroll panes in it.
        splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,
                                   listScrollPane, pictureScrollPane);
        splitPane.setOneTouchExpandable(true);
        splitPane.setDividerLocation(150);

        //Provide minimum sizes for the two components in the split pane.
        Dimension minimumSize = new Dimension(100, 50);
        listScrollPane.setMinimumSize(minimumSize);
        pictureScrollPane.setMinimumSize(minimumSize);

        //Provide a preferred size for the split pane.
        splitPane.setPreferredSize(new Dimension(400, 200));
    }

    //Used by SplitPaneDemo2
    public JList getImageList() {
        return list;
    }

    public JSplitPane getSplitPane() {
        return splitPane;
    }

    public void valueChanged(ListSelectionEvent e) {
        if (e.getValueIsAdjusting())
            return;

        JList theList = (JList)e.getSource();
        if (theList.isSelectionEmpty()) {
            picture.setIcon(null);
            picture.setText(null);
        } else {
            int index = theList.getSelectedIndex();
            ImageIcon newImage = createImageIcon("images/" +
                                     (String)imageNames.elementAt(index));
            picture.setIcon(newImage);
            if (newImage != null) {
                picture.setText(null);
            } else {
                picture.setText("Image not found: "
                                + (String)imageNames.elementAt(index));
            }
        }
    }

    protected static Vector parseList(String theStringList) {
        Vector v = new Vector(10);
        StringTokenizer tokenizer = new StringTokenizer(theStringList, " ");
        while (tokenizer.hasMoreTokens()) {
            String image = tokenizer.nextToken();
            v.addElement(image);
        }
        return v;
    }

    /** Called when the image property file can't be found. */
    private void handleMissingResource(MissingResourceException e) {
        System.err.println();
        System.err.println("Can't find the properties file " +
                           "that contains the image names.");
        System.err.println("Its name should be imagenames.properties, " +
                           "and it should");
        System.err.println("contain a single line that specifies " +
                           "one or more image");
        System.err.println("files to be found in a directory " +
                           "named images.  Example:");
        System.err.println();
        System.err.println("    images=Bird.gif Cat.gif Dog.gif");
        System.err.println();
        throw(e);  //Used to be exit(1), but that causes the console to
                   //go away under Java Web Start; this way, you're
                   //more likely to see a relevant error message.
    }

    /** Returns an ImageIcon, or null if the path was invalid. */
    protected static ImageIcon createImageIcon(String path) {
        java.net.URL imgURL = SplitPaneDemo.class.getResource(path);
        if (imgURL != null) {
            return new ImageIcon(imgURL);
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
        JDialog.setDefaultLookAndFeelDecorated(true);

        //Create and set up the window.
        JFrame frame = new JFrame("SplitPaneDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        SplitPaneDemo splitPaneDemo = new SplitPaneDemo();
        frame.getContentPane().add(splitPaneDemo.getSplitPane());

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
