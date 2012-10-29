/*
 * DragFileDemo.java is a 1.4 example that
 * requires the following file:
 *    FileAndTextTransferHandler.java
 *    TabbedPaneController.java
 */
import java.awt.event.*;
import java.awt.*;
import javax.swing.*;

public class DragFileDemo extends JPanel
                          implements ActionListener {
    JTextArea fileArea;
    JFileChooser fc;
    JButton clear;
    TabbedPaneController tpc;

    public DragFileDemo() {
        super(new BorderLayout());

        fc = new JFileChooser();;
        fc.setMultiSelectionEnabled(true);
        fc.setDragEnabled(true);
        fc.setControlButtonsAreShown(false);
        JPanel fcPanel = new JPanel(new BorderLayout());
        fcPanel.add(fc, BorderLayout.CENTER);

        clear = new JButton("Clear All");
        clear.addActionListener(this);
        JPanel buttonPanel = new JPanel(new BorderLayout());
        buttonPanel.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));
        buttonPanel.add(clear, BorderLayout.LINE_END);

        JPanel upperPanel = new JPanel(new BorderLayout());
        upperPanel.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));
        upperPanel.add(fcPanel, BorderLayout.CENTER);
        upperPanel.add(buttonPanel, BorderLayout.PAGE_END);

        //The TabbedPaneController manages the panel that
        //contains the tabbed pane.  When there are no files
        //the panel contains a plain text area.  Then, as
        //files are dropped onto the area, the tabbed panel 
        //replaces the file area.
        JTabbedPane tabbedPane = new JTabbedPane();
        JPanel tabPanel = new JPanel(new BorderLayout());
        tabPanel.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));
        tpc = new TabbedPaneController(tabbedPane, tabPanel);

        JSplitPane splitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT,
            upperPanel, tabPanel);
        splitPane.setDividerLocation(400);
        splitPane.setPreferredSize(new Dimension(530, 650));
        add(splitPane, BorderLayout.CENTER);
    }

    public void setDefaultButton() {
        getRootPane().setDefaultButton(clear);
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == clear) {
            tpc.clearAll();
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
        JFrame frame = new JFrame("DragFileDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the menu bar and content pane.
        DragFileDemo demo = new DragFileDemo();
        demo.setOpaque(true); //content panes must be opaque
        frame.setContentPane(demo);

        //Display the window.
        frame.pack();
        frame.setVisible(true);
        demo.setDefaultButton();
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
