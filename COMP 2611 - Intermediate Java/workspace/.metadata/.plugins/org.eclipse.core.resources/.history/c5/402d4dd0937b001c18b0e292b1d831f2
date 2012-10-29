import java.awt.*;
import java.awt.event.*;
import javax.swing.JComponent;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JFrame;
import javax.swing.JTextField;
import javax.swing.JTextArea;

/*
 * FocusConceptsDemo.java is a 1.4 example that
 * requires no other files.
 */
public class FocusConceptsDemo extends JPanel {

    static JFrame frame;
    JTextField t1, t2, t3, t4;
    JButton b1, b2, b3, b4;
    JTextArea text1;

    public FocusConceptsDemo() {
        super(new BorderLayout());

        b1 = new JButton("JButton");
        b2 = new JButton("JButton");
        b3 = new JButton("JButton");
        b4 = new JButton("JButton");
        JPanel buttonPanel = new JPanel(new GridLayout(1,1));
        buttonPanel.add(b1);
        buttonPanel.add(b2);
        buttonPanel.add(b3);
        buttonPanel.add(b4);

        text1 = new JTextArea("JTextArea", 15, 40);
        JPanel textAreaPanel = new JPanel(new BorderLayout());
        textAreaPanel.add(text1, BorderLayout.CENTER);

        t1 = new JTextField("JTextField");
        t2 = new JTextField("JTextField");
        t3 = new JTextField("JTextField");
        t4 = new JTextField("JTextField");
        JPanel textFieldPanel = new JPanel(new GridLayout(1,1));
        textFieldPanel.add(t1);
        textFieldPanel.add(t2);
        textFieldPanel.add(t3);
        textFieldPanel.add(t4);

        add(buttonPanel, BorderLayout.PAGE_START);
        add(textAreaPanel, BorderLayout.CENTER);
        add(textFieldPanel, BorderLayout.PAGE_END);
        setBorder(BorderFactory.createEmptyBorder(20,20,20,20));
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
        frame = new JFrame("FocusConceptsDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        JComponent newContentPane = new FocusConceptsDemo();
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
