import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/*
 * ProgressBarDemo2.java is a 1.4 application that requires these files:
 *   LongTask.java
 *   SwingWorker.java
 */
public class ProgressBarDemo2 extends JPanel
                              implements ActionListener {
    public final static int ONE_SECOND = 1000;

    private JProgressBar progressBar;
    private Timer timer;
    private JButton startButton;
    private LongTask task;
    private JTextArea taskOutput;
    private String newline = "\n";

    public ProgressBarDemo2() {
        super(new BorderLayout());
        task = new LongTask();

        //Create the demo's UI.
        startButton = new JButton("Start");
        startButton.setActionCommand("start");
        startButton.addActionListener(this);

        progressBar = new JProgressBar(0, task.getLengthOfTask());
        progressBar.setValue(0);

        //We call setStringPainted, even though we don't want the
        //string to show up until we switch to determinate mode,
        //so that the progress bar height stays the same whether
        //or not the string is shown.
        progressBar.setStringPainted(true); //get space for the string
        progressBar.setString("");          //but don't paint it

        taskOutput = new JTextArea(5, 20);
        taskOutput.setMargin(new Insets(5,5,5,5));
        taskOutput.setEditable(false);

        JPanel panel = new JPanel();
        panel.add(startButton);
        panel.add(progressBar);

        add(panel, BorderLayout.PAGE_START);
        add(new JScrollPane(taskOutput), BorderLayout.CENTER);
        setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

        //Create a timer.
        timer = new Timer(ONE_SECOND, new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
                progressBar.setValue(task.getCurrent());
                String s = task.getMessage();
                if (s != null) {
                    if (progressBar.isIndeterminate()) {
                        progressBar.setIndeterminate(false);
                        progressBar.setString(null); //display % string
                    }
                    taskOutput.append(s + newline);
                    taskOutput.setCaretPosition(
                            taskOutput.getDocument().getLength());
                }
                if (task.isDone()) {
                    Toolkit.getDefaultToolkit().beep();
                    timer.stop();
                    startButton.setEnabled(true);
                    progressBar.setValue(progressBar.getMinimum());
                    progressBar.setString(""); //hide % string
                }
            }
        });
    }

    /**
     * Called when the user presses the start button.
     */
    public void actionPerformed(ActionEvent evt) {
        progressBar.setIndeterminate(true);
        startButton.setEnabled(false);
        task.go();
        timer.start();
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
        JFrame frame = new JFrame("ProgressBarDemo2");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        JComponent newContentPane = new ProgressBarDemo2();
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
