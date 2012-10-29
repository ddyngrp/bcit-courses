/*
 * MyDemo1.java is a 1.4 example that requires no other files. 
 */
import javax.swing.JFrame;
import javax.swing.JLabel;
import java.awt.Font;
import java.awt.BorderLayout;  

public class MyDemo1 {
    /**
     * Create the GUI and show it.  For thread safety,
     * this method should be invoked from the
     * event-dispatching thread.
     */
    private static void createAndShowGUI() {
        //Make sure we have nice window decorations.
        JFrame.setDefaultLookAndFeelDecorated(true);

        //Create and set up the window.
        JFrame frame = new JFrame("MyDemo1");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Add a label with bold italic font.
        JLabel label = new JLabel("My Demo");
        frame.getContentPane().add(BorderLayout.CENTER, label);
        if (true) {
            label.setFont(label.getFont().deriveFont(Font.ITALIC | Font.BOLD));
        } else {
            //another way of doing it, but not as appropriate since 
            //setFont is faster than using HTML.
            label.setText("<html><i>My Demo</i></html>");
        }
        label.setHorizontalAlignment(JLabel.CENTER);

        //Display the window, making it a little bigger than it really needs to be.
        frame.pack();
        frame.setSize(frame.getWidth() + 100, frame.getHeight() + 50);
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
