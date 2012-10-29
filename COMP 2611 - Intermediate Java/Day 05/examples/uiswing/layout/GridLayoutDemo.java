/*
 * GridLayoutDemo.java is a 1.4 application that requires no other files.
 */

import java.awt.*;
import javax.swing.*;

public class GridLayoutDemo {
    public final static boolean RIGHT_TO_LEFT = false;

    public static void addComponentsToPane(Container pane) {
        if (RIGHT_TO_LEFT) {
            pane.setComponentOrientation(
                ComponentOrientation.RIGHT_TO_LEFT);
        }

        pane.setLayout(new GridLayout(0,2));

        pane.add(new JButton("Button 1"));
        pane.add(new JButton("Button 2"));
        pane.add(new JButton("Button 3"));
        pane.add(new JButton("Long-Named Button 4"));
        pane.add(new JButton("5"));
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
        JFrame frame = new JFrame("GridLayoutDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Set up the content pane.
        addComponentsToPane(frame.getContentPane());

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
