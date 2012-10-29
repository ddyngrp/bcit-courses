import javax.swing.JFrame;

/*
 * A 1.4 application that extends SpinnerDemo to allow easy
 * execution of the demo with a cycling Months spinner.
 * Other files required:
 *   SpinnerDemo.java
 *   CyclingSpinnerListModel.java
 *   SpringUtilities.java
 */

public class SpinnerDemo2 extends SpinnerDemo {
    public SpinnerDemo2() {
        super(true); //turn on cycling for the months spinner
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
        JFrame frame = new JFrame("SpinnerDemo2");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        SpinnerDemo2 newContentPane = new SpinnerDemo2();
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
