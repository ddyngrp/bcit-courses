import java.awt.*;
import java.awt.event.*;
import javax.swing.JComponent;
import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JFrame;
import javax.swing.JTextField;
import javax.swing.JTable;
import javax.swing.JCheckBox;

/*
 * FocusTraversalDemo.java is a 1.4 example that
 * requires no other files.
 */
public class FocusTraversalDemo extends JPanel
                        implements ActionListener {

    static JFrame frame;
    JTextField tf1, tf2, tf3, tf4, tf5, tf6;
    JTable table;
    JLabel label;
    JCheckBox togglePolicy;
    static MyOwnFocusTraversalPolicy newPolicy;


    public FocusTraversalDemo() {
        super(new BorderLayout());
        newPolicy = new MyOwnFocusTraversalPolicy();

        tf1 = new JTextField("Field 1");
        tf2 = new JTextField("A Bigger Field 2");
        tf3 = new JTextField("Field 3");
        tf4 = new JTextField("A Bigger Field 4");
        tf5 = new JTextField("Field 5");
        tf6 = new JTextField("A Bigger Field 6");
        table = new JTable(4,3);
        togglePolicy = new JCheckBox("Custom FocusTraversalPolicy");
        togglePolicy.setActionCommand("toggle");
        togglePolicy.addActionListener(this);
        togglePolicy.setFocusable(false);  //Remove it from the focus cycle.
        //Note that HTML is allowed and will break this run of text
        //across two lines.
        label = new JLabel("<html>Use Tab (or Shift-Tab) to navigate from component to component.<p>Control-Tab (or Control-Shift-Tab) allows you to break out of the JTable.</html>");

        JPanel leftTextPanel = new JPanel(new GridLayout(3,2));
        leftTextPanel.add(tf1, BorderLayout.PAGE_START);
        leftTextPanel.add(tf3, BorderLayout.CENTER);
        leftTextPanel.add(tf5, BorderLayout.PAGE_END);
        leftTextPanel.setBorder(BorderFactory.createEmptyBorder(0,0,5,5));
        JPanel rightTextPanel = new JPanel(new GridLayout(3,2));
        rightTextPanel.add(tf2, BorderLayout.PAGE_START);
        rightTextPanel.add(tf4, BorderLayout.CENTER);
        rightTextPanel.add(tf6, BorderLayout.PAGE_END);
        rightTextPanel.setBorder(BorderFactory.createEmptyBorder(0,0,5,5));
        JPanel tablePanel = new JPanel(new GridLayout(0,1));
        tablePanel.add(table, BorderLayout.CENTER);
        tablePanel.setBorder(BorderFactory.createEtchedBorder());
        JPanel bottomPanel = new JPanel(new GridLayout(2,1));
        bottomPanel.add(togglePolicy, BorderLayout.PAGE_START);
        bottomPanel.add(label, BorderLayout.PAGE_END);

        add(leftTextPanel, BorderLayout.LINE_START);
        add(rightTextPanel, BorderLayout.CENTER);
        add(tablePanel, BorderLayout.LINE_END);
        add(bottomPanel, BorderLayout.PAGE_END);
        setBorder(BorderFactory.createEmptyBorder(20,20,20,20));
    }

    //Turn the custom focus traversal policy on/off,
    //according to the checkbox
    public void actionPerformed(ActionEvent e) {
        if ("toggle".equals(e.getActionCommand())) {
            frame.setFocusTraversalPolicy(togglePolicy.isSelected() ?
                    newPolicy : null);
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
        frame = new JFrame("FocusTraversalDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        JComponent newContentPane = new FocusTraversalDemo();
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

    public class MyOwnFocusTraversalPolicy
                 extends FocusTraversalPolicy {

        public Component getComponentAfter(Container focusCycleRoot,
                                           Component aComponent) {
            if (aComponent.equals(tf1)) {
                return tf2;
            } else if (aComponent.equals(tf2)) {
                return tf3;
            } else if (aComponent.equals(tf3)) {
                return tf4;
            } else if (aComponent.equals(tf4)) {
                return tf5;
            } else if (aComponent.equals(tf5)) {
                return tf6;
            } else if (aComponent.equals(tf6)) {
                return table;
            } else if (aComponent.equals(table)) {
                return tf1;
            }
            return tf1;
        }

        public Component getComponentBefore(Container focusCycleRoot,
                                       Component aComponent) {
            if (aComponent.equals(tf1)) {
                return table;
            } else if (aComponent.equals(tf2)) {
                return tf1;
            } else if (aComponent.equals(tf3)) {
                return tf2;
            } else if (aComponent.equals(tf4)) {
                return tf3;
            } else if (aComponent.equals(tf5)) {
                return tf4;
            } else if (aComponent.equals(tf6)) {
                return tf5;
            } else if (aComponent.equals(table)) {
                return tf6;
            }
            return tf1;
        }

        public Component getDefaultComponent(Container focusCycleRoot) {
            return tf1;
        }

        public Component getLastComponent(Container focusCycleRoot) {
            return table;
        }

        public Component getFirstComponent(Container focusCycleRoot) {
            return tf1;
        }
    }
}
