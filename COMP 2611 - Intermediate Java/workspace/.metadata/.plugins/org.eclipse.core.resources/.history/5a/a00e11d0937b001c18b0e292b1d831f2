/*
 * DragColorTextFieldDemo.java is a 1.4 example that requires
 * the following files:
 *     ColorTransferHandler.java
 *     ColorAndTextTransferHandler.java
 */
 
import java.io.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.datatransfer.*;
import java.awt.dnd.*;
import javax.swing.*;
import javax.swing.text.*;

/**
 * Example code that shows a text component that both
 * accepts color (by changing its foreground) and also
 * exports simple text.
 */
public class DragColorTextFieldDemo extends JPanel {
    JCheckBox toggleForeground;
    ColorAndTextTransferHandler colorHandler;
    
    public DragColorTextFieldDemo() {
        super(new BorderLayout());
        JTextField textField;

        setBorder(BorderFactory.createEmptyBorder(20,20,20,20));

        JColorChooser chooser = new JColorChooser();
        chooser.setDragEnabled(true);
        add(chooser, BorderLayout.PAGE_START);

        //Create the color transfer handler.
        colorHandler = new ColorAndTextTransferHandler();
        
        //Create some text fields.
        JPanel buttonPanel = new JPanel(new GridLayout(3, 1));
        textField = new JTextField("I can accept color/text and drag text.");
        textField.setTransferHandler(colorHandler);
        textField.setDragEnabled(true);
        buttonPanel.add(textField);
        textField = new JTextField("Me too!");
        textField.setTransferHandler(colorHandler);
        textField.setDragEnabled(true);
        buttonPanel.add(textField);
        textField = new JTextField("Me three!");
        textField.setTransferHandler(colorHandler);
        textField.setDragEnabled(true);
        buttonPanel.add(textField);
        add(buttonPanel, BorderLayout.CENTER);
    }

    //Create an Edit menu to support cut/copy/paste.
    public JMenuBar createMenuBar () {
        JMenuItem menuItem = null;
        JMenuBar menuBar = new JMenuBar();
        JMenu mainMenu = new JMenu("Edit");
        mainMenu.setMnemonic(KeyEvent.VK_E);

        menuItem = new JMenuItem(new DefaultEditorKit.CutAction());
        menuItem.setText("Cut");
        menuItem.setMnemonic(KeyEvent.VK_T);
        mainMenu.add(menuItem);
        menuItem = new JMenuItem(new DefaultEditorKit.CopyAction());
        menuItem.setText("Copy");
        menuItem.setMnemonic(KeyEvent.VK_C);
        mainMenu.add(menuItem);
        menuItem = new JMenuItem(new DefaultEditorKit.PasteAction());
        menuItem.setText("Paste");
        menuItem.setMnemonic(KeyEvent.VK_P);
        mainMenu.add(menuItem);

        menuBar.add(mainMenu);
        return menuBar;
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
        JFrame frame = new JFrame("DragColorTextFieldDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the menu bar and content pane.
        DragColorTextFieldDemo demo = new DragColorTextFieldDemo();
        frame.setJMenuBar(demo.createMenuBar());
        demo.setOpaque(true); //content panes must be opaque
        frame.setContentPane(demo);

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
