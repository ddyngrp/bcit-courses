/*
 * GridLayoutDemo.java is a 1.4 application that requires one
 * other file:
 *   GraphPaperLayout.java
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class GraphPaperTest extends JPanel {
    public GraphPaperTest() {
        setLayout(new GraphPaperLayout(new Dimension(5,5)));

        //Add a 1x1 Rect at (0,0).
        add(new JButton("1"), new Rectangle(0,0,1,1));

        //Add a 2x1 Rect at (2,0).
        add(new JButton("2"), new Rectangle(2,0,2,1));

        //Add a 1x2 Rect at (1,1).
        add(new JButton("3"), new Rectangle(1,1,1,2));

        //Add a 2x2 Rect at (3,2).
        add(new JButton("4"), new Rectangle(3,2,2,2));

        //Add a 1x1 Rect at (0,4).
        add(new JButton("5"), new Rectangle(0,4,1,1));

        //Add a 1x2 Rect at (2,3).
        add(new JButton("6"), new Rectangle(2,3,1,2));
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
        JFrame frame = new JFrame("GraphPaperTest");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        JComponent newContentPane = new GraphPaperTest();
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
