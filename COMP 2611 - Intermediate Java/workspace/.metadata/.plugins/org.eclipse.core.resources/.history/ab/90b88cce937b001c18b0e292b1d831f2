import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.beans.*;

/*
 * SplitPaneDividerDemo.java is a 1.4 application that requires the following files:
 *   SizeDisplayer.java
 *   images/Cat.gif
 *   images/Dog.gif
 */
public class SplitPaneDividerDemo extends JPanel
                                  implements ActionListener {

    private JSplitPane splitPane;
    
    public SplitPaneDividerDemo() {
        super(new BorderLayout());

        Font font = new Font("Serif", Font.ITALIC, 24);

        ImageIcon icon = createImageIcon("images/Cat.gif");
        SizeDisplayer sd1 = new SizeDisplayer("left", icon);
        sd1.setMinimumSize(new Dimension(30,30));
        sd1.setFont(font);
        
        icon = createImageIcon("images/Dog.gif");
        SizeDisplayer sd2 = new SizeDisplayer("right", icon);
        sd2.setMinimumSize(new Dimension(60,60));
        sd2.setFont(font);
        
        splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,
                                   sd1, sd2);
        splitPane.setResizeWeight(0.5);
        splitPane.setOneTouchExpandable(true);
        splitPane.setContinuousLayout(true);
        
        add(splitPane, BorderLayout.CENTER);
        add(createControlPanel(), BorderLayout.PAGE_END);
    }

    private JComponent createControlPanel() {
        JPanel panel = new JPanel();
        JButton reset = new JButton("Reset");
        reset.addActionListener(this);
        panel.add(reset);
        return panel;
    }
    
    //Required by ActionListener interface. Respond to reset button.
    public void actionPerformed(ActionEvent e) {
        splitPane.resetToPreferredSizes();
    }
    
    /** Returns an ImageIcon, or null if the path was invalid. */
    private static ImageIcon createImageIcon(String path) {
        java.net.URL imgURL = SplitPaneDividerDemo.class.getResource(path);
        if (imgURL != null) {
            return new ImageIcon(imgURL);
        } else {
            System.err.println("Couldn't find file: " + path);
            return null;
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
        JFrame frame = new JFrame("SplitPaneDividerDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        SplitPaneDividerDemo newContentPane = new SplitPaneDividerDemo();
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
