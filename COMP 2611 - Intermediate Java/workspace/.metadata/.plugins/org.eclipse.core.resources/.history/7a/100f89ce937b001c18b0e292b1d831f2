/*
 * A 1.4 application that demonstrates using spinners.
 * Other files required:
 *   SpringUtilities.java
 *   CyclingSpinnerListModel.java
 */

import javax.swing.*;
import java.awt.Color;
import java.awt.Container;
import java.util.Calendar;
import java.util.Date;

public class SpinnerDemo extends JPanel {
    public SpinnerDemo(boolean cycleMonths) {
        super(new SpringLayout());

        String[] labels = {"Month: ", "Year: ", "Another Date: "};
        int numPairs = labels.length;
        Calendar calendar = Calendar.getInstance();
        JFormattedTextField ftf = null;

        //Add the first label-spinner pair.
        String[] monthStrings = getMonthStrings(); //get month names
        SpinnerListModel monthModel = null;
        if (cycleMonths) { //use custom model
            monthModel = new CyclingSpinnerListModel(monthStrings);
        } else { //use standard model
            monthModel = new SpinnerListModel(monthStrings);
        }
        JSpinner spinner = addLabeledSpinner(this,
                                             labels[0],
                                             monthModel);
        //Tweak the spinner's formatted text field.
        ftf = getTextField(spinner);
        if (ftf != null ) {
            ftf.setColumns(8); //specify more width than we need
            ftf.setHorizontalAlignment(JTextField.RIGHT);
        }


        //Add second label-spinner pair.
        int currentYear = calendar.get(Calendar.YEAR);
        SpinnerModel yearModel = new SpinnerNumberModel(currentYear, //initial value
                                       currentYear - 100, //min
                                       currentYear + 100, //max
                                       1);                //step
        //If we're cycling, hook this model up to the month model.
        if (monthModel instanceof CyclingSpinnerListModel) {
            ((CyclingSpinnerListModel)monthModel).setLinkedModel(yearModel);
        }
        spinner = addLabeledSpinner(this, labels[1], yearModel);
        //Make the year be formatted without a thousands separator.
        spinner.setEditor(new JSpinner.NumberEditor(spinner, "#"));


        //Add the third label-spinner pair.
        Date initDate = calendar.getTime();
        calendar.add(Calendar.YEAR, -100);
        Date earliestDate = calendar.getTime();
        calendar.add(Calendar.YEAR, 200);
        Date latestDate = calendar.getTime();
        SpinnerModel dateModel = new SpinnerDateModel(initDate,
                                     earliestDate,
                                     latestDate,
                                     Calendar.YEAR);//ignored for user input
        spinner = addLabeledSpinner(this, labels[2], dateModel);
        spinner.setEditor(new JSpinner.DateEditor(spinner, "MM/yyyy"));
        //Tweak the spinner's formatted text field.
        ftf = getTextField(spinner);
        if (ftf != null ) {
            ftf.setHorizontalAlignment(JTextField.RIGHT);
            ftf.setBorder(BorderFactory.createEmptyBorder(1,1,1,3));
        }
        spinner.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));
        //XXX: No easy way to get to the buttons and change their border.

        //Lay out the panel.
        SpringUtilities.makeCompactGrid(this,
                                        numPairs, 2, //rows, cols
                                        10, 10,        //initX, initY
                                        6, 10);       //xPad, yPad
    }

    /**
     * Return the formatted text field used by the editor, or
     * null if the editor doesn't descend from JSpinner.DefaultEditor.
     */
    public JFormattedTextField getTextField(JSpinner spinner) {
        JComponent editor = spinner.getEditor();
        if (editor instanceof JSpinner.DefaultEditor) {
            return ((JSpinner.DefaultEditor)editor).getTextField();
        } else {
            System.err.println("Unexpected editor type: "
                               + spinner.getEditor().getClass()
                               + " isn't a descendant of DefaultEditor");
            return null;
        }
    }

    /**
     * DateFormatSymbols returns an extra, empty value at the
     * end of the array of months.  Remove it.
     */
    static protected String[] getMonthStrings() {
        String[] months = new java.text.DateFormatSymbols().getMonths();
        int lastIndex = months.length - 1;

        if (months[lastIndex] == null
           || months[lastIndex].length() <= 0) { //last item empty
            String[] monthStrings = new String[lastIndex];
            System.arraycopy(months, 0,
                             monthStrings, 0, lastIndex);
            return monthStrings;
        } else { //last item not empty
            return months;
        }
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
        JFrame frame = new JFrame("SpinnerDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        JComponent newContentPane = new SpinnerDemo(false);
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
