import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.colorchooser.*;

/* 
 * ColorChooserDemo2.java is a 1.4 application that requires these files:
 *   CrayonPanel.java
 *   images/red.gif
 *   images/yellow.gif
 *   images/green.gif
 *   images/blue.gif
 */
public class ColorChooserDemo2 extends JPanel
                               implements ActionListener,
                                          ChangeListener {
    public JLabel banner;
    public JColorChooser tcc;

    public ColorChooserDemo2() {
        super(new BorderLayout());

        //Set up banner to use as custom preview panel
        banner = new JLabel("Welcome to the Tutorial Zone!",
                            JLabel.CENTER);
        banner.setForeground(Color.yellow);
        banner.setBackground(Color.blue);
        banner.setOpaque(true);
        banner.setFont(new Font("SansSerif", Font.BOLD, 24));
        banner.setPreferredSize(new Dimension(100, 65));

        JPanel bannerPanel = new JPanel(new BorderLayout());
        bannerPanel.add(banner, BorderLayout.CENTER);
        bannerPanel.setBorder(BorderFactory.createTitledBorder("Banner"));

        //Set up color chooser for setting background color
        JPanel panel = new JPanel(); //use FlowLayout
        JButton bcc = new JButton("Show Color Chooser...");
        bcc.addActionListener(this);
        panel.add(bcc);
        panel.setBorder(BorderFactory.createTitledBorder(
                                "Choose Background Color"));

        //Set up color chooser for setting text color
        tcc = new JColorChooser();
        tcc.getSelectionModel().addChangeListener(this);
        tcc.setBorder(BorderFactory.createTitledBorder("Choose Text Color"));

        //Remove the preview panel
        tcc.setPreviewPanel(new JPanel());

        //Override the chooser panels with our own
        AbstractColorChooserPanel panels[] = { new CrayonPanel() };
        tcc.setChooserPanels(panels);
        tcc.setColor(banner.getForeground());

        add(bannerPanel, BorderLayout.PAGE_START);
        add(panel, BorderLayout.CENTER);
        add(tcc, BorderLayout.PAGE_END);
    }

    public void actionPerformed(ActionEvent e) {
        Color newColor = JColorChooser.showDialog(
                                       ColorChooserDemo2.this,
                                       "Choose Background Color",
                                       banner.getBackground());
        if (newColor != null) {
            banner.setBackground(newColor);
        }
    }

    public void stateChanged(ChangeEvent e) {
        Color newColor = tcc.getColor();
        banner.setForeground(newColor);
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
        JFrame frame = new JFrame("ColorChooserDemo2");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        JComponent newContentPane = new ColorChooserDemo2();
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
