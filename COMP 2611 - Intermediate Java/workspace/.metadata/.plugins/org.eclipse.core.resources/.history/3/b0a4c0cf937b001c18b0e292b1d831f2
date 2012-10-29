/*
 * A 1.4 application that uses SpringLayout to create a compact grid.
 * Other files required: SpringUtilities.java.
 */

import javax.swing.*;
import java.awt.*;

public class SpringCompactGrid {
    /**
     * Create the GUI and show it.  For thread safety,
     * this method should be invoked from the
     * event-dispatching thread.
     */
    private static void createAndShowGUI() {
        JPanel panel = new JPanel(new SpringLayout());

        int rows = 10;
        int cols = 10;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                int anInt = (int) Math.pow(r, c);
                JTextField textField =
                        new JTextField(Integer.toString(anInt));
                panel.add(textField);
            }
        }

        //Lay out the panel.
        SpringUtilities.makeCompactGrid(panel, //parent
                                        rows, cols,
                                        3, 3,  //initX, initY
                                        3, 3); //xPad, yPad

        //Make sure we have nice window decorations.
        JFrame.setDefaultLookAndFeelDecorated(true);

        //Create and set up the window.
        JFrame frame = new JFrame("SpringCompactGrid");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Set up the content pane.
        panel.setOpaque(true); //content panes must be opaque
        frame.setContentPane(panel);

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
