import javax.swing.*;
import java.awt.Font;

public class HelloJWS {
    /**
     * Create the GUI and show it.  For thread safety,
     * this method should be invoked from the
     * event-dispatching thread.
     */
    private static void createAndShowGUI() {
        //Make sure we have nice window decorations.
        JFrame.setDefaultLookAndFeelDecorated(true);

        //Create and set up the window.
        JFrame frame = new JFrame("HelloJWS");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Add the "HelloJWS" label.
        JLabel label = new JLabel();
        label.setHorizontalAlignment(JLabel.CENTER);
        label.setFont(label.getFont().deriveFont(Font.PLAIN));
        frame.getContentPane().add(label);

        //Set label text after testing for Java Web Start.
        String text = null;
        try {
            Class sm = javax.jnlp.ServiceManager.class;
            
            //If we reach this line, we're running in an environment
            //such as Java Web Start that provides JNLP services.
            text = "<html>You're running an application "
                 + "using Java<font size=-2><sup>TM</sup></font> "
                 + "Web Start!</html>";
        } catch (java.lang.NoClassDefFoundError e) {
            //If no ServiceManager, we're not in Java Web Start.
            text = "<html>You're running an application, "
                 + "but <b>not</b> using "
                 + "Java<font size=-2><sup>TM</sup></font> "
                 + "Web Start!</html>";
        }
        label.setText(text);

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