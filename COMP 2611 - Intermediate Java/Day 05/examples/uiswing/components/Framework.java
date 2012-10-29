import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;

import javax.swing.JOptionPane;

import java.awt.*;
import java.awt.event.*;

/* Framework.java requires no other files. */
public class Framework extends WindowAdapter {
    public int numWindows = 0;
    private Point lastLocation = null;
    private int maxX = 500;
    private int maxY = 500;

    public Framework() {
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        maxX = screenSize.width - 50;
        maxY = screenSize.height - 50;
        makeNewWindow();
    }

    public void makeNewWindow() {
        JFrame frame = new MyFrame(this);
        numWindows++;
        System.out.println("Number of windows: " + numWindows);

        if (lastLocation != null) {
            //Move the window over and down 40 pixels.
            lastLocation.translate(40, 40);
            if ((lastLocation.x > maxX) || (lastLocation.y > maxY)) {
                lastLocation.setLocation(0, 0);
            }
            frame.setLocation(lastLocation);
        } else {
            lastLocation = frame.getLocation();
        }

        System.out.println("Frame location: " + lastLocation);
        frame.setVisible(true);
    }

    //This method must be evoked from the event-dispatching thread.
    public void quit(JFrame frame) {
        if (quitConfirmed(frame)) {
            System.out.println("Quitting.");
            System.exit(0);
        }
        System.out.println("Quit operation not confirmed; staying alive.");
    }

    private boolean quitConfirmed(JFrame frame) {
        String s1 = "Quit";
        String s2 = "Cancel";
        Object[] options = {s1, s2};
        int n = JOptionPane.showOptionDialog(frame,
                "Windows are still open.\nDo you really want to quit?",
                "Quit Confirmation",
                JOptionPane.YES_NO_OPTION,
                JOptionPane.QUESTION_MESSAGE,
                null,
                options,
                s1);
        if (n == JOptionPane.YES_OPTION) {
            return true;
        } else {
            return false;
        }
    }

    public void windowClosed(WindowEvent e) {
        numWindows--;
        System.out.println("Number of windows = " + numWindows);
        if (numWindows <= 0) {
            System.out.println("All windows gone.  Bye bye!");
            System.exit(0);
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
        JDialog.setDefaultLookAndFeelDecorated(true);

        Framework framework = new Framework();
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

    class MyFrame extends JFrame {
        protected Dimension defaultSize = new Dimension(200, 200);
        protected Framework framework = null;

        public MyFrame(Framework controller) {
            super("New Frame");
            framework = controller;
            setDefaultCloseOperation(DISPOSE_ON_CLOSE);
            addWindowListener(framework);

            JMenu menu = new JMenu("Window");
            menu.setMnemonic(KeyEvent.VK_W);
            JMenuItem item = null;
            //close
            item = new JMenuItem("Close");
            item.setMnemonic(KeyEvent.VK_C);
            item.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    System.out.println("Close window");
                    MyFrame.this.setVisible(false);
                    MyFrame.this.dispose();
                }
            });
            menu.add(item);

            //new
            item = new JMenuItem("New");
            item.setMnemonic(KeyEvent.VK_N);
            item.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    System.out.println("New window");
                    framework.makeNewWindow();
                }
            });
            menu.add(item);

            //quit
            item = new JMenuItem("Quit");
            item.setMnemonic(KeyEvent.VK_Q);
            item.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    System.out.println("Quit request");
                    framework.quit(MyFrame.this);
                }
            });
            menu.add(item);

            JMenuBar menuBar = new JMenuBar();
            menuBar.add(menu);
            setJMenuBar(menuBar);

            setSize(defaultSize);
        }
    }
}


