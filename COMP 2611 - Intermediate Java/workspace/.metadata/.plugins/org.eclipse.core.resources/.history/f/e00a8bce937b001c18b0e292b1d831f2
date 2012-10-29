/*
 * A 1.4 application that demonstrates using spinners.
 * Other files required:
 *   SpringUtilities.java
 */

import javax.swing.*;
import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class SpinnerDemo4 extends JPanel {
    public SpinnerDemo4() {
        super(new SpringLayout());

        String[] labels = {"Shade of Gray: "};
        int numPairs = labels.length;

        JSpinner spinner = addLabeledSpinner(this,
                                             labels[0],
                                             new GrayModel(170));
        spinner.setEditor(new GrayEditor(spinner));

        //Lay out the panel.
        SpringUtilities.makeCompactGrid(this,
                                        numPairs, 2, //rows, cols
                                        10, 10,        //initX, initY
                                        6, 10);       //xPad, yPad
    }

    static protected JSpinner addLabeledSpinner(Container c,
                                                String label,
                                                SpinnerModel model) {
        JLabel l = new JLabel(label);
        c.add(l);

        JSpinner spinner = new JSpinner(model);
        l.setLabelFor(spinner);
        c.add(spinner);

        return spinner;
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
        JFrame frame = new JFrame("SpinnerDemo4");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        JComponent newContentPane = new SpinnerDemo4();
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

    class GrayModel extends SpinnerNumberModel {
        public GrayModel(int value) {
            super(value, 0, 255, 5);
        }

        public int getIntValue() {
            Integer myValue = (Integer)getValue();
            return myValue.intValue();
        }

        public Color getColor() {
            int intValue = getIntValue();
            return new Color(intValue, intValue, intValue);
        }
    }

    class GrayEditor extends JLabel
                     implements ChangeListener {
        public GrayEditor(JSpinner spinner) {
            setOpaque(true);

            //Get info from the model.
            GrayModel myModel = (GrayModel)(spinner.getModel());
            setBackground(myModel.getColor());
            spinner.addChangeListener(this);

            //Set tool tip text.
            updateToolTipText(spinner);

            //Set size info.
            Dimension size = new Dimension(60, 15);
            setMinimumSize(size);
            setPreferredSize(size);
        }

        protected void updateToolTipText(JSpinner spinner) {
            String toolTipText = spinner.getToolTipText();
            if (toolTipText != null) {
                //JSpinner has tool tip text.  Use it.
                if (!toolTipText.equals(getToolTipText())) {
                    setToolTipText(toolTipText);
                }
            } else {
                //Define our own tool tip text.
                GrayModel myModel = (GrayModel)(spinner.getModel());
                int rgb = myModel.getIntValue();
                setToolTipText("(" + rgb + "," + rgb + "," + rgb + ")");
            }
        }

        public void stateChanged(ChangeEvent e) {
            JSpinner mySpinner = (JSpinner)(e.getSource());
            GrayModel myModel = (GrayModel)(mySpinner.getModel());
            setBackground(myModel.getColor());
            updateToolTipText(mySpinner);
        }
    }
}
