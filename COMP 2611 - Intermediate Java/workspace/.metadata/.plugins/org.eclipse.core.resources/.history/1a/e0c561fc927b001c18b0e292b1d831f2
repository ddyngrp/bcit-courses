/*
 * LabelDnD2.java is a 1.4 example that
 * requires no other files.
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

//LabelDnD2 allows dropping color onto the foreground
//of the JLabel.
public class LabelDnD2 extends JPanel {
    JTextField textField;
    JLabel label;

    public LabelDnD2() {
        super(new BorderLayout());

        JColorChooser chooser = new JColorChooser();
        chooser.setDragEnabled(true);

        label = new JLabel("I'm a Label and I accept color!",
           SwingConstants.LEADING);
        label.setTransferHandler(new TransferHandler("foreground"));

        MouseListener listener = new DragMouseAdapter();
        label.addMouseListener(listener);
        JPanel lpanel = new JPanel(new GridLayout(1,1));
        TitledBorder t2 = BorderFactory.createTitledBorder(
           "JLabel: drop color onto the label");
        lpanel.add(label);
        lpanel.setBorder(t2);

        add(chooser, BorderLayout.CENTER);
        add(lpanel,  BorderLayout.PAGE_END);
        setBorder(BorderFactory.createEmptyBorder(5,5,5,5));
    }

    private class DragMouseAdapter extends MouseAdapter {
        public void mousePressed(MouseEvent e) {
            JComponent c = (JComponent)e.getSource();
            TransferHandler handler = c.getTransferHandler();
            handler.exportAsDrag(c, e, TransferHandler.COPY);
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

        //Create and set up the window.
        JFrame frame = new JFrame("LabelDnD2");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        JComponent newContentPane = new LabelDnD2();
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
