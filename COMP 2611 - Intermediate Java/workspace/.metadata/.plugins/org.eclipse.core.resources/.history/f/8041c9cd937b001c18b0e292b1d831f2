import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 * @author ges
 * @author kwalrath
 */
/* MenuGlueDemo.java is a 1.4 application that requires no other files. */
public class MenuGlueDemo {
    public JMenuBar createMenuBar() {
        JMenuBar menuBar = new JMenuBar();
        menuBar.add(createMenu("Menu 1"));
        menuBar.add(createMenu("Menu 2"));
        menuBar.add(Box.createHorizontalGlue());
        menuBar.add(createMenu("Menu 3"));
        return menuBar;
    }

    public JMenu createMenu(String title) {
        JMenu m = new JMenu(title);
        m.add("Menu item #1 in " + title);
        m.add("Menu item #2 in " + title);
        m.add("Menu item #3 in " + title);
        return m;
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
        JFrame frame = new JFrame("MenuGlueDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        MenuGlueDemo demo = new MenuGlueDemo();
        frame.setContentPane(demo.createMenuBar());

        //Display the window.
        frame.setSize(300, 100);
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
