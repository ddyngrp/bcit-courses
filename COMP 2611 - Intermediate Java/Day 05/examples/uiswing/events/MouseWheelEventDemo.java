/*
 * MouseWheelEventDemo.java is a 1.4 example
 * that requires no other files.
 */

import javax.swing.*;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;

import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;

public class MouseWheelEventDemo extends JPanel
                            implements MouseWheelListener {
    JTextArea textArea;
    JScrollPane scrollPane;
    final static String newline = "\n";

    public MouseWheelEventDemo() {
        super(new BorderLayout());

        textArea = new JTextArea();
        textArea.setEditable(false);
        scrollPane = new JScrollPane(textArea);
        scrollPane.setVerticalScrollBarPolicy(
                JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        scrollPane.setPreferredSize(new Dimension(400, 250));
        add(scrollPane, BorderLayout.CENTER);
        textArea.append("This text area displays information "
                      + "about its mouse wheel events."
                      + newline);

        //Register for mouse-wheel events on the text area.
        textArea.addMouseWheelListener(this);

        setPreferredSize(new Dimension(450, 350));
        setBorder(BorderFactory.createEmptyBorder(20,20,20,20));
    }

    public void mouseWheelMoved(MouseWheelEvent e) {
       String message;
       int notches = e.getWheelRotation();
       if (notches < 0) {
           message = "Mouse wheel moved UP "
                        + -notches + " notch(es)" + newline;
       } else {
           message = "Mouse wheel moved DOWN "
                        + notches + " notch(es)" + newline;
       }
       if (e.getScrollType() == MouseWheelEvent.WHEEL_UNIT_SCROLL) {
           message += "    Scroll type: WHEEL_UNIT_SCROLL" + newline;
           message += "    Scroll amount: " + e.getScrollAmount()
                   + " unit increments per notch" + newline;
           message += "    Units to scroll: " + e.getUnitsToScroll()
                   + " unit increments" + newline;
           message += "    Vertical unit increment: "
               + scrollPane.getVerticalScrollBar().getUnitIncrement(1)
               + " pixels" + newline;
       } else { //scroll type == MouseWheelEvent.WHEEL_BLOCK_SCROLL
           message += "    Scroll type: WHEEL_BLOCK_SCROLL" + newline;
           message += "    Vertical block increment: "
               + scrollPane.getVerticalScrollBar().getBlockIncrement(1)
               + " pixels" + newline;
       }
       saySomething(message, e);
    }

    //Append to the text area and make sure the new text is visible.
    void saySomething(String eventDescription, MouseWheelEvent e) {
        textArea.append(e.getComponent().getClass().getName()
                        + ": "
                        + eventDescription);
        textArea.setCaretPosition(textArea.getDocument().getLength());
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
        JFrame frame = new JFrame("MouseWheelEventDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        JComponent newContentPane = new MouseWheelEventDemo();
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
