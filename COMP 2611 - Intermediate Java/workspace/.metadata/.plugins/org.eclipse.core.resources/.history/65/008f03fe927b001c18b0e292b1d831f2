import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 * @author ges
 * @author kwalrath
 */
/* MenuLayoutDemo.java is a 1.4 application that requires no other files. */

public class MenuLayoutDemo {
    public JMenuBar createMenuBar() {
        JMenuBar menuBar = new JMenuBar();
        menuBar.setLayout(new BoxLayout(menuBar, BoxLayout.PAGE_AXIS));
        menuBar.add(createMenu("Menu 1"));
        menuBar.add(createMenu("Menu 2"));
        menuBar.add(createMenu("Menu 3"));

        menuBar.setBorder(BorderFactory.createMatteBorder(0,0,0,1,
                                                          Color.BLACK));
        return menuBar;
    }

    // used by createMenuBar
    public JMenu createMenu(String title) {
        JMenu m = new HorizontalMenu(title);
        m.add("Menu item #1 in " + title);
        m.add("Menu item #2 in " + title);
        m.add("Menu item #3 in " + title);

        JMenu submenu = new HorizontalMenu("Submenu");
        submenu.add("Submenu item #1");
        submenu.add("Submenu item #2");
        m.add(submenu);

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
        JFrame frame = new JFrame("MenuLayoutDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        MenuLayoutDemo demo = new MenuLayoutDemo();
        Container contentPane = frame.getContentPane();
        contentPane.setBackground(Color.WHITE); //contrasting bg
        contentPane.add(demo.createMenuBar(),
                        BorderLayout.LINE_START);

        //Display the window.
        frame.setSize(300, 150);
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

    class HorizontalMenu extends JMenu {
        HorizontalMenu(String label) {
            super(label);
            JPopupMenu pm = getPopupMenu();
            pm.setLayout(new BoxLayout(pm, BoxLayout.LINE_AXIS));
        }

        public Dimension getMinimumSize() {
            return getPreferredSize();
        }

        public Dimension getMaximumSize() {
            return getPreferredSize();
        }

        public void setPopupMenuVisible(boolean b) {
            boolean isVisible = isPopupMenuVisible();
            if (b != isVisible) {
                if ((b==true) && isShowing()) {
                    //Set location of popupMenu (pulldown or pullright).
                    //Perhaps this should be dictated by L&F.
                    int x = 0;
                    int y = 0;
                    Container parent = getParent();
                    if (parent instanceof JPopupMenu) {
                        x = 0;
                        y = getHeight();
                    } else {
                        x = getWidth();
                        y = 0;
                    }
                    getPopupMenu().show(this, x, y);
                } else {
                    getPopupMenu().setVisible(false);
                }
            }
        }
    }
}
