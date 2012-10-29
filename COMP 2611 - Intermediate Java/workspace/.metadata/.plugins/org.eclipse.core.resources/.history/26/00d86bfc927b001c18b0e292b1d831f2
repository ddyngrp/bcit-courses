/*
 * DragPictureDemo2.java is a 1.4 example that
 * requires the following files:
 *     Picture.java
 *     DTPicture.java
 *     PictureTransferHandler.java
 *     TransferActionListener.java
 *     images/Maya.jpg
 *     images/Anya.jpg
 *     images/Laine.jpg
 *     images/Cosmo.jpg
 *     images/Adele.jpg
 *     images/Alexi.jpg
 */
import java.io.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.datatransfer.*;
import java.awt.dnd.*;
import javax.swing.*;

//A version of DragPictureDemo that creates an
//Edit menu with cut/copy/paste actions.
//This demo adds a class called TransferActionDemo
//that transfers the cut/copy/paste menu action
//to the currently focused component.
public class DragPictureDemo2 extends JPanel {

    DTPicture pic1, pic2, pic3, pic4,  pic5,  pic6,
              pic7, pic8, pic9, pic10, pic11, pic12;
    static String mayaString = "Maya";
    static String anyaString = "Anya";
    static String laineString = "Laine";
    static String cosmoString = "Cosmo";
    static String adeleString = "Adele";
    static String alexiString = "Alexi";
    PictureTransferHandler picHandler;

    public DragPictureDemo2() {
        super(new BorderLayout());
        picHandler = new PictureTransferHandler();
        //Since we are using keyboard accelerators, we don't
        //need the component to install its own input map
        //bindings.
        DTPicture.setInstallInputMapBindings(false);

        JPanel mugshots = new JPanel(new GridLayout(4, 3));
        pic1 = new DTPicture(createImageIcon("images/" +
                    mayaString + ".jpg", mayaString).getImage());
        pic1.setTransferHandler(picHandler);
        mugshots.add(pic1);
        pic2 = new DTPicture(createImageIcon("images/" +
                    anyaString + ".jpg", anyaString).getImage());
        pic2.setTransferHandler(picHandler);
        mugshots.add(pic2);
        pic3 = new DTPicture(createImageIcon("images/" +
                    laineString + ".jpg", laineString).getImage());
        pic3.setTransferHandler(picHandler);
        mugshots.add(pic3);
        pic4 = new DTPicture(createImageIcon("images/" +
                    cosmoString + ".jpg", cosmoString).getImage());
        pic4.setTransferHandler(picHandler);
        mugshots.add(pic4);
        pic5 = new DTPicture(createImageIcon("images/" +
                    adeleString + ".jpg", adeleString).getImage());
        pic5.setTransferHandler(picHandler);
        mugshots.add(pic5);
        pic6 = new DTPicture(createImageIcon("images/" +
                    alexiString + ".jpg", alexiString).getImage());
        pic6.setTransferHandler(picHandler);
        mugshots.add(pic6);

        //These six components with no pictures provide handy
        //drop targets.
        pic7 = new DTPicture(null);
        pic7.setTransferHandler(picHandler);
        mugshots.add(pic7);
        pic8 = new DTPicture(null);
        pic8.setTransferHandler(picHandler);
        mugshots.add(pic8);
        pic9 = new DTPicture(null);
        pic9.setTransferHandler(picHandler);
        mugshots.add(pic9);
        pic10 = new DTPicture(null);
        pic10.setTransferHandler(picHandler);
        mugshots.add(pic10);
        pic11 = new DTPicture(null);
        pic11.setTransferHandler(picHandler);
        mugshots.add(pic11);
        pic12 = new DTPicture(null);
        pic12.setTransferHandler(picHandler);
        mugshots.add(pic12);

        setPreferredSize(new Dimension(450, 630));
        add(mugshots, BorderLayout.CENTER);
        setBorder(BorderFactory.createEmptyBorder(20,20,20,20));
    }

    //Create an Edit menu to support cut/copy/paste.
    public JMenuBar createMenuBar() {
        JMenuItem menuItem = null;
        JMenuBar menuBar = new JMenuBar();
        JMenu mainMenu = new JMenu("Edit");
        mainMenu.setMnemonic(KeyEvent.VK_E);
        TransferActionListener actionListener = new TransferActionListener();

        menuItem = new JMenuItem("Cut");
        menuItem.setActionCommand((String)TransferHandler.getCutAction().
                 getValue(Action.NAME));
        menuItem.addActionListener(actionListener);
        menuItem.setAccelerator(
          KeyStroke.getKeyStroke(KeyEvent.VK_X, ActionEvent.CTRL_MASK));
        menuItem.setMnemonic(KeyEvent.VK_T);
        mainMenu.add(menuItem);
        menuItem = new JMenuItem("Copy");
        menuItem.setActionCommand((String)TransferHandler.getCopyAction().
                 getValue(Action.NAME));
        menuItem.addActionListener(actionListener);
        menuItem.setAccelerator(
          KeyStroke.getKeyStroke(KeyEvent.VK_C, ActionEvent.CTRL_MASK));
        menuItem.setMnemonic(KeyEvent.VK_C);
        mainMenu.add(menuItem);
        menuItem = new JMenuItem("Paste");
        menuItem.setActionCommand((String)TransferHandler.getPasteAction().
                 getValue(Action.NAME));
        menuItem.addActionListener(actionListener);
        menuItem.setAccelerator(
          KeyStroke.getKeyStroke(KeyEvent.VK_V, ActionEvent.CTRL_MASK));
        menuItem.setMnemonic(KeyEvent.VK_P);
        mainMenu.add(menuItem);

        menuBar.add(mainMenu);
        return menuBar;
    }

    /** Returns an ImageIcon, or null if the path was invalid. */
    protected static ImageIcon createImageIcon(String path,
                                               String description) {
        java.net.URL imageURL = DragPictureDemo2.class.getResource(path);

        if (imageURL == null) {
            System.err.println("Resource not found: "
                               + path);
            return null;
        } else {
            return new ImageIcon(imageURL, description);
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

        //Create and set up the window.
        JFrame frame = new JFrame("DragPictureDemo2");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the menu bar and content pane.
        DragPictureDemo2 demo = new DragPictureDemo2();
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
