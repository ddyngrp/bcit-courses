/*
 * DragColorDemo.java is a 1.4 example that requires 
 * the following file:
 *    ColorTransferHandler.java
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.datatransfer.*;
import java.awt.dnd.*;
import java.io.*;

/**
 * Example code that shows any JComponent can be customized to
 * allow dropping of a color.
 */
public class DragColorDemo extends JPanel
                           implements ActionListener {
    JCheckBox toggleForeground;
    ColorTransferHandler colorHandler;
    
    public DragColorDemo() {
        super(new BorderLayout());
        setBorder(BorderFactory.createEmptyBorder(20,20,20,20));

        JColorChooser chooser = new JColorChooser();
        chooser.setDragEnabled(true);
        add(chooser, BorderLayout.PAGE_START);

        //Create the color transfer handler.
        colorHandler = new ColorTransferHandler();
        
        //Create a matrix of 9 buttons.
        JPanel buttonPanel = new JPanel(new GridLayout(3, 3));
        for (int i = 0; i < 9; i++) {
            JButton tmp = new JButton("Button "+i);
            tmp.setTransferHandler(colorHandler);
            buttonPanel.add(tmp);
        }
        add(buttonPanel, BorderLayout.CENTER);

        //Create a check box.
        toggleForeground = new JCheckBox(
            "Change the foreground color.");
        toggleForeground.setSelected(true);
        toggleForeground.addActionListener(this);
        JPanel textPanel = new JPanel(new BorderLayout());
        textPanel.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));
        textPanel.add(toggleForeground, BorderLayout.PAGE_START);

        //Create a label.
        JLabel label = new JLabel(
         "Change the color of any button or this label by dropping a color.");
        label.setTransferHandler(colorHandler);
        label.setOpaque(true); //So the background color can be changed.
        textPanel.add(label, BorderLayout.PAGE_END);
        add(textPanel, BorderLayout.PAGE_END);
    }

    public void actionPerformed(ActionEvent e) {
        colorHandler.
           setChangesForegroundColor(toggleForeground.isSelected());
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
        JFrame frame = new JFrame("DragColorDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and setup the content pane.
        JComponent newContentPane = new DragColorDemo();
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
