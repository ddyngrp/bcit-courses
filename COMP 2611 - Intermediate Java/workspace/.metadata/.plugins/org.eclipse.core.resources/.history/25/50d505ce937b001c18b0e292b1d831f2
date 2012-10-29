import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/*
 * ProgressMonitorDemo.java is a 1.4 application that requires these files:
 *   LongTask.java
 *   SwingWorker.java
 */
public class ProgressMonitorDemo extends JPanel
                                 implements ActionListener {
    public final static int ONE_SECOND = 1000;

    private ProgressMonitor progressMonitor;
    private Timer timer;
    private JButton startButton;
    private LongTask task;
    private JTextArea taskOutput;
    private String newline = "\n";

    public ProgressMonitorDemo() {
        super(new BorderLayout());
        task = new LongTask();

        //Create the demo's UI.
        startButton = new JButton("Start");
        startButton.setActionCommand("start");
        startButton.addActionListener(this);

        taskOutput = new JTextArea(5, 20);
        taskOutput.setMargin(new Insets(5,5,5,5));
        taskOutput.setEditable(false);

        add(startButton, BorderLayout.PAGE_START);
        add(new JScrollPane(taskOutput), BorderLayout.CENTER);
        setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

        //Create a timer.
        timer = new Timer(ONE_SECOND, new TimerListener());
    }

    /**
     * The actionPerformed method in this class
     * is called each time the Timer "goes off".
     */
    class TimerListener implements ActionListener {
        public void actionPerformed(ActionEvent evt) {
            progressMonitor.setProgress(task.getCurrent());
            String s = task.getMessage();
            if (s != null) {
                progressMonitor.setNote(s);
                taskOutput.append(s + newline);
                taskOutput.setCaretPosition(
                    taskOutput.getDocument().getLength());
            }
            if (progressMonitor.isCanceled() || task.isDone()) {
                progressMonitor.close();
                task.stop();
                Toolkit.getDefaultToolkit().beep();
                timer.stop();
                if (task.isDone()) {
                    taskOutput.append("Task completed." + newline);
                } else {
                    taskOutput.append("Task canceled." + newline);

                }
                startButton.setEnabled(true);
            }
        }
    }

    /**
     * Called when the user presses the start button.
     */
    public void actionPerformed(ActionEvent evt) {
        progressMonitor = new ProgressMonitor(ProgressMonitorDemo.this,
                                  "Running a Long Task",
                                  "", 0, task.getLengthOfTask());
        progressMonitor.setProgress(0);
        progressMonitor.setMillisToDecideToPopup(2 * ONE_SECOND);

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
        JFrame frame = new JFrame("ProgressMonitorDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        JComponent newContentPane = new ProgressMonitorDemo();
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
