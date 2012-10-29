/*
 * A 1.4 class used by the Converter example.
 */

import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.text.NumberFormat;
import javax.swing.text.NumberFormatter;
import java.beans.*; //property change stuff

public class ConversionPanel extends JPanel
                             implements ActionListener,
                                        ChangeListener,
                                        PropertyChangeListener {
    JFormattedTextField textField;
    JComboBox unitChooser;
    JSlider slider;
    ConverterRangeModel sliderModel;
    Converter controller;
    Unit[] units;
    String title;
    NumberFormat numberFormat;

    final static boolean MULTICOLORED = false;
    final static int MAX = 10000;

    ConversionPanel(Converter myController, String myTitle,
                    Unit[] myUnits,
                    ConverterRangeModel myModel) {
        if (MULTICOLORED) {
            setOpaque(true);
            setBackground(new Color(0, 255, 255));
        }
        setBorder(BorderFactory.createCompoundBorder(
                        BorderFactory.createTitledBorder(myTitle),
                        BorderFactory.createEmptyBorder(5,5,5,5)));

        //Save arguments in instance variables.
        controller = myController;
        units = myUnits;
        title = myTitle;
        sliderModel = myModel;

        //Create the text field format, and then the text field.
        numberFormat = NumberFormat.getNumberInstance();
        numberFormat.setMaximumFractionDigits(2);
        NumberFormatter formatter = new NumberFormatter(numberFormat);
        formatter.setAllowsInvalid(false);
        formatter.setCommitsOnValidEdit(true);//seems to be a no-op --
        //aha -- it changes the value property but doesn't cause the result to
        //be parsed (that happens on focus loss/return, I think).
        //
        textField = new JFormattedTextField(formatter);
        textField.setColumns(10);
        textField.setValue(new Double(sliderModel.getDoubleValue()));
        textField.addPropertyChangeListener(this);

        //Add the combo box.
        unitChooser = new JComboBox();
        for (int i = 0; i < units.length; i++) { //Populate it.
            unitChooser.addItem(units[i].description);
        }
        unitChooser.setSelectedIndex(0);
        sliderModel.setMultiplier(units[0].multiplier);
        unitChooser.addActionListener(this);

        //Add the slider.
        slider = new JSlider(sliderModel);
        sliderModel.addChangeListener(this);

        //Make the text field/slider group a fixed size
        //to make stacked ConversionPanels nicely aligned.
        JPanel unitGroup = new JPanel() {
            public Dimension getMinimumSize() {
                return getPreferredSize();
            }
            public Dimension getPreferredSize() {
                return new Dimension(150,
                                     super.getPreferredSize().height);
            }
            public Dimension getMaximumSize() {
                return getPreferredSize();
            }
        };
        unitGroup.setLayout(new BoxLayout(unitGroup,
                                          BoxLayout.PAGE_AXIS));
        if (MULTICOLORED) {
            unitGroup.setOpaque(true);
            unitGroup.setBackground(new Color(0, 0, 255));
        }
        unitGroup.setBorder(BorderFactory.createEmptyBorder(
                                                0,0,0,5));
        unitGroup.add(textField);
        unitGroup.add(slider);

        //Create a subpanel so the combo box isn't too tall
        //and is sufficiently wide.
        JPanel chooserPanel = new JPanel();
        chooserPanel.setLayout(new BoxLayout(chooserPanel,
                                             BoxLayout.PAGE_AXIS));
        if (MULTICOLORED) {
            chooserPanel.setOpaque(true);
            chooserPanel.setBackground(new Color(255, 0, 255));
        }
        chooserPanel.add(unitChooser);
        chooserPanel.add(Box.createHorizontalStrut(100));

        //Put everything together.
        setLayout(new BoxLayout(this, BoxLayout.LINE_AXIS));
        add(unitGroup);
        add(chooserPanel);
        unitGroup.setAlignmentY(TOP_ALIGNMENT);
        chooserPanel.setAlignmentY(TOP_ALIGNMENT);
    }

    //Don't allow this panel to get taller than its preferred size.
    //BoxLayout pays attention to maximum size, though most layout
    //managers don't.
    public Dimension getMaximumSize() {
        return new Dimension(Integer.MAX_VALUE,
                             getPreferredSize().height);
    }

    /**
     * Returns the multiplier (units/meter) for the currently
     * selected unit of measurement.
     */
    public double getMultiplier() {
        return sliderModel.getMultiplier();
    }

    public double getValue() {
        return sliderModel.getDoubleValue();
    }

    /** Updates the text field when the main data model is updated. */
    public void stateChanged(ChangeEvent e) {
        int min = sliderModel.getMinimum();
        int max = sliderModel.getMaximum();
        double value = sliderModel.getDoubleValue();
        NumberFormatter formatter = (NumberFormatter)textField.getFormatter();

        formatter.setMinimum(new Double(min));
        formatter.setMaximum(new Double(max));
        textField.setValue(new Double(value));
    }

    /**
     * Responds to the user choosing a new unit from the combo box.
     */
    public void actionPerformed(ActionEvent e) {
        //Combo box event. Set new maximums for the sliders.
        int i = unitChooser.getSelectedIndex();
        sliderModel.setMultiplier(units[i].multiplier);
        controller.resetMaxValues(false);
    }

    /**
     * Detects when the value of the text field (not necessarily the same
     * number as you'd get from getText) changes.
     */
    public void propertyChange(PropertyChangeEvent e) {
        if ("value".equals(e.getPropertyName())) {
            Number value = (Number)e.getNewValue();
            sliderModel.setDoubleValue(value.doubleValue());
        }
    }
}
