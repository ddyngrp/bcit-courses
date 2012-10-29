/*
 * Beeper1.java is a version of the 1.4 Beeper.java example
 * that beeps when the user finishes entering data into a
 * text field.
 */

import java.awt.*;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.JTextField;
import javax.swing.JComponent;

import java.awt.Toolkit;
import java.awt.BorderLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class Beeper1 extends JPanel 
                    implements ActionListener {
    JButton button;
    JTextField textField;

    public Beeper1() {
        super(new BorderLayout());
	textField = new JTextField(20);
	add(textField, BorderLayout.CENTER);
	//The object registered as the action
	//listener is informed when the user
	//has finished entering text; for example
	//by pressing Enter.
	textField.addActionListener(this);
	
        button = new JButton("Click Me");
        add(button, BorderLayout.PAGE_END);
        button.addActionListener(this);
    }

    public void actionPerformed(ActionEvent e) {
        Toolkit.getDefaultToolkit().beep();
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
        JFrame frame = new JFrame("Beeper2");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        JComponent newContentPane = new Beeper1();
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
