/**
 * Project: lab05
 * File: Lab4.java
 * Date: 15-Oct-07
 * Time: 9:47:19 PM
 */
package a00683006.labs;

import java.awt.*;

import javax.swing.*;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class Lab5 {
	private JFrame frame;
	private JPanel ageInputPane, ageCalcPane;
	private JTextField yearField;
	private JLabel yearLabel, monthLabel, dayLabel, ageLabel;
	private JButton ageCalc;
	private JComboBox monthList;
	private JSpinner daySpinner;
	private static final String[] months = {"January", "February", "March", "April",
		"May", "June", "July", "August", "September", "October", "November", "December"};

	public Lab5() {
		// Create and setup the windows
		frame = new JFrame("Calculate Age");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(300, 150);
		frame.setLocationRelativeTo(null); // open in the centre of the screen
		
		// Create and setup panels.
		ageInputPane = new JPanel(new GridBagLayout());
		ageInputPane.setAlignmentY(JPanel.TOP_ALIGNMENT);
		ageCalcPane = new JPanel(new GridBagLayout());
		ageCalcPane.setAlignmentY(JPanel.BOTTOM_ALIGNMENT);
		ageCalcPane.setBackground(Color.lightGray);
		
		// Add all the interface elements
		addElements();
		
		// Sets the default button
		frame.getRootPane().setDefaultButton(ageCalc);
		
		// Add panels to the window frame.
		frame.getContentPane().add(ageInputPane, BorderLayout.PAGE_START);
		frame.getContentPane().add(ageCalcPane, BorderLayout.PAGE_END);
		
		// Display the window.
		frame.setVisible(true);
	}
	
	/**
	 * Create and add the interface elements.
	 */
	private void addElements() {
		ageInputPane.setComponentOrientation(ComponentOrientation.LEFT_TO_RIGHT);
		ageCalcPane.setComponentOrientation(ComponentOrientation.LEFT_TO_RIGHT);
		GridBagConstraints gbc = new GridBagConstraints();
		gbc.fill = GridBagConstraints.HORIZONTAL;
		
		// Set text labels, alignments, and formatting
		yearLabel = new JLabel("Year");
		yearLabel.setHorizontalAlignment(JLabel.CENTER);
		monthLabel = new JLabel("Month");
		monthLabel.setHorizontalAlignment(JLabel.CENTER);
		dayLabel = new JLabel("Day");
		dayLabel.setHorizontalAlignment(JLabel.CENTER);
		ageLabel = new JLabel("Your age is:");
		ageLabel.setFont(new Font("Arial Bold", Font.ITALIC, 24));
		
		// Set inputs
		yearField = new JTextField();
		monthList = new JComboBox(months);
		daySpinner = new JSpinner(new SpinnerNumberModel(1, 1, 31, 1));
		
		// Set buttons
		ageCalc = new JButton("Calculate Age");
		
		// Add elements to the panel
		gbc.gridx = 0;
		gbc.gridy = 0;
		gbc.weightx = 0.5;
		ageInputPane.add(yearLabel, gbc);
		gbc.gridx = 1;
		ageInputPane.add(monthLabel, gbc);
		gbc.gridx = 2;
		ageInputPane.add(dayLabel, gbc);
		gbc.gridy = 1;
		gbc.gridx = 0;
		ageInputPane.add(yearField, gbc);
		gbc.gridx = 1;
		ageInputPane.add(monthList, gbc);
		gbc.gridx = 2;
		ageInputPane.add(daySpinner, gbc);
		gbc.gridx = 1;
		gbc.gridy = 2;
		gbc.weighty = 1.0; // request remaining vertical space
		gbc.anchor = GridBagConstraints.PAGE_START;
		ageInputPane.add(ageCalc, gbc);
		gbc.gridx = 0;
		gbc.gridy = 3;
		gbc.gridwidth = 3;
		gbc.insets = new Insets(10,0,10,0);  // padding
		gbc.anchor = GridBagConstraints.PAGE_END;
		ageCalcPane.add(ageLabel, gbc);
	}
	
	/**
     * Create the GUI and show it. For thread safety,
     * this method should be invoked from the
     * event-dispatching thread.
     */
    private static void createAndShowGUI() {
        // Make sure we have nice window decorations.
        JFrame.setDefaultLookAndFeelDecorated(true);
        
        new Lab5();
    }
    
	/**
	 * @param args
	 */
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