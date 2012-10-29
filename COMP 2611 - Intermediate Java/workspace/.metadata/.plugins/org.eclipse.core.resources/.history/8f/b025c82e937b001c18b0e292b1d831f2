/*
 * FocusEventDemo.java is a 1.4 example that requires
 * no other files.
 */

import java.util.Vector;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class FocusEventDemo extends JPanel
                            implements FocusListener {
    final static String newline = "\n";
    JTextArea display;

    public FocusEventDemo() {
        super(new GridBagLayout());
        GridBagLayout gridbag = (GridBagLayout)getLayout();
        GridBagConstraints c = new GridBagConstraints();

        c.fill = GridBagConstraints.HORIZONTAL;
        c.weightx = 1.0;  //Make column as wide as possible.
        JTextField textField = new JTextField("A TextField");
        textField.setMargin(new Insets(0,2,0,2));
        textField.addFocusListener(this);
        gridbag.setConstraints(textField, c);
        add(textField);

        c.weightx = 0.1;  //Widen every other column a bit, when possible. 
        c.fill = GridBagConstraints.NONE;
        JLabel label = new JLabel("A Label");
        label.setBorder(BorderFactory.createEmptyBorder(0,5,0,5));
        label.addFocusListener(this);
        gridbag.setConstraints(label, c);
        add(label);

        String comboPrefix = "ComboBox Item #";
        final int numItems = 15;
        Vector vector = new Vector(numItems);
        for (int i = 0; i < numItems; i++) {
            vector.addElement(comboPrefix + i);
        }
        JComboBox comboBox = new JComboBox(vector);
        comboBox.addFocusListener(this);
        gridbag.setConstraints(comboBox, c);
        add(comboBox);

        c.gridwidth = GridBagConstraints.REMAINDER;
        JButton button = new JButton("A Button");
        button.addFocusListener(this);
        gridbag.setConstraints(button, c);
        add(button);

        c.weightx = 0.0;   
        c.weighty = 0.1;
        c.fill = GridBagConstraints.BOTH;
        String listPrefix = "List Item #";
        Vector listVector = new Vector(numItems);
        for (int i = 0; i < numItems; i++) {
            listVector.addElement(listPrefix + i);
        }
        JList list = new JList(listVector);
        list.setSelectedIndex(1); //It's easier to see the focus change
                                  //if an item is selected.
        list.addFocusListener(this);
        JScrollPane listScrollPane = new JScrollPane(list);
        //We want to prevent the list's scroll bars
        //from getting the focus - even with the keyboard.
        //Note that in general we prefer setRequestFocusable
        //over setFocusable for reasons of accessibility, 
        //but this is to work around bug #4866958.
        listScrollPane.getVerticalScrollBar().setFocusable(false);
        listScrollPane.getHorizontalScrollBar().setFocusable(false);
        gridbag.setConstraints(listScrollPane, c);
        add(listScrollPane);

        c.weighty = 1.0; //Make this row as tall as possible.
        c.gridheight = GridBagConstraints.REMAINDER;
        //Set up the area that reports focus-gained and focus-lost events.
        display = new JTextArea();
        display.setEditable(false);
        //The method setRequestFocusEnabled prevents a
        //component from being clickable, but it can still
        //get the focus through the keyboard - this ensures
        //user accessibility.
        display.setRequestFocusEnabled(false);
        display.addFocusListener(this);
        JScrollPane displayScrollPane = new JScrollPane(display);

        //Work around for bug #4866958.
        displayScrollPane.getHorizontalScrollBar().setFocusable(false);
        displayScrollPane.getVerticalScrollBar().setFocusable(false);
        gridbag.setConstraints(displayScrollPane, c);
        add(displayScrollPane);

        setPreferredSize(new Dimension(450, 450));
        setBorder(BorderFactory.createEmptyBorder(20,20,20,20));
    }

    public void focusGained(FocusEvent e) {
        displayMessage("Focus gained", e);
    }

    public void focusLost(FocusEvent e) {
        displayMessage("Focus lost", e);
    }

    void displayMessage(String prefix, FocusEvent e) {
        display.append(prefix
                       + (e.isTemporary() ? " (temporary):" : ":")
                       + e.getComponent().getClass().getName()
                       + "; Opposite component: "
                       + (e.getOppositeComponent() != null ?
                          e.getOppositeComponent().getClass().getName() : "null")
                       + newline); 
        display.setCaretPosition(display.getDocument().getLength());
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
        JFrame frame = new JFrame("FocusEventDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        JComponent newContentPane = new FocusEventDemo();
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
