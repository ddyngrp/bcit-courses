/*
 * Swing version
 */

import javax.swing.*;

import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.Dimension;
import java.awt.Color;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class MultiListener extends JPanel 
                           implements ActionListener {
    JTextArea topTextArea;
    JTextArea bottomTextArea;
    JButton button1, button2;
    final static String newline = "\n";

    public MultiListener() {
        super(new GridBagLayout());
        GridBagLayout gridbag = (GridBagLayout)getLayout();
        GridBagConstraints c = new GridBagConstraints();

        JLabel l = null;

        c.fill = GridBagConstraints.BOTH;
        c.gridwidth = GridBagConstraints.REMAINDER;
        l = new JLabel("What MultiListener hears:");
        gridbag.setConstraints(l, c);
        add(l);

        c.weighty = 1.0;
        topTextArea = new JTextArea();
        topTextArea.setEditable(false);
        JScrollPane topScrollPane = new JScrollPane(topTextArea);
        Dimension preferredSize = new Dimension(200, 75);
        topScrollPane.setPreferredSize(preferredSize);
        gridbag.setConstraints(topScrollPane, c);
        add(topScrollPane);

        c.weightx = 0.0;
        c.weighty = 0.0;
        l = new JLabel("What Eavesdropper hears:");
        gridbag.setConstraints(l, c);
        add(l);

        c.weighty = 1.0;
        bottomTextArea = new JTextArea();
        bottomTextArea.setEditable(false);
        JScrollPane bottomScrollPane = new JScrollPane(bottomTextArea);
        bottomScrollPane.setPreferredSize(preferredSize);
        gridbag.setConstraints(bottomScrollPane, c);
        add(bottomScrollPane);

        c.weightx = 1.0;
        c.weighty = 0.0;
        c.gridwidth = 1;
        c.insets = new Insets(10, 10, 0, 10);
        button1 = new JButton("Blah blah blah");
        gridbag.setConstraints(button1, c);
        add(button1);

        c.gridwidth = GridBagConstraints.REMAINDER;
        button2 = new JButton("You don't say!");
        gridbag.setConstraints(button2, c);
        add(button2);

        button1.addActionListener(this);
        button2.addActionListener(this);

        button2.addActionListener(new Eavesdropper(bottomTextArea));

        setPreferredSize(new Dimension(450, 450));
        setBorder(BorderFactory.createCompoundBorder(
                                BorderFactory.createMatteBorder(
                                                1,1,2,2,Color.black),
                                BorderFactory.createEmptyBorder(5,5,5,5)));
    }

    public void actionPerformed(ActionEvent e) {
        topTextArea.append(e.getActionCommand() + newline);
        topTextArea.setCaretPosition(topTextArea.getDocument().getLength());
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
        JFrame frame = new JFrame("MultiListener");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        JComponent newContentPane = new MultiListener();
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

class Eavesdropper implements ActionListener {
    JTextArea myTextArea;
    public Eavesdropper(JTextArea ta) {
        myTextArea = ta;
    }

    public void actionPerformed(ActionEvent e) {
        myTextArea.append(e.getActionCommand()
                        + MultiListener.newline);
        myTextArea.setCaretPosition(myTextArea.getDocument().getLength());
    }
}
