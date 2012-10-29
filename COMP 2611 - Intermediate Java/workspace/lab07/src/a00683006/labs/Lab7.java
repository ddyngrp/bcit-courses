/**
 * Project: lab 07
 * File: Delete.java
 * Date: 29-Oct-07
 * Time: 11:59:54 PM
 */
package a00683006.labs;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

/**
 * @author Steffen L. Norgren, A00683006
 * 
 */
public class Lab7 extends JFrame implements ActionListener {

	private static final long serialVersionUID = 461829739875L;
	private static final String OUTPUT = "Your age is: ";
	private static final Font OUTPUT_FONT = new Font("Arial Bold", Font.ITALIC,
			24);
	private static final String[] MONTHS = { "January", "February", "March",
			"April", "May", "June", "July", "August", "September", "October",
			"November", "December" };

	private JTextField yearOfBirthField;
	private JComboBox monthList;
	private JSpinner daySpinner;
	private JButton calculateAge;
	private MyLabel outputAge;

	public static void main(String[] args) {
		Lab7 lab = new Lab7();

		// Configures the JFrame
		lab.create();
		lab.setSize(420, 200);
		lab.setLocationRelativeTo(null);
		lab.setVisible(true);
		lab.setDefaultCloseOperation(EXIT_ON_CLOSE);
	}

	/**
	 * Default constructor. All this does is set the window title.
	 */
	private Lab7() {
		super("Calculate Age"); // Sets the window title
	}

	/**
	 * Creates and sets all the elements associated with the JFrame.
	 */
	private void create() {

		// JFrame container for all the panels
		Container contentPane = this.getContentPane();

		JPanel fieldsPanel = new JPanel(); // Create a new panel for the fields
		JPanel actionPanel = new JPanel(); // Create a new panel for the
		// buttons
		JPanel displayPanel = new JPanel(); // Create a new panel for the
		// results

		// Create the input fields
		yearOfBirthField = new JTextField(4);
		monthList = new JComboBox(MONTHS);
		daySpinner = new JSpinner(new SpinnerNumberModel(1, 1, 31, 1));

		// Configures the fieldsPanel and adds associated elements
		fieldsPanel.setLayout(new GridLayout(2, 3));
		fieldsPanel.add(new MyLabel("Year"));
		fieldsPanel.add(new MyLabel("Month"));
		fieldsPanel.add(new MyLabel("Day"));
		fieldsPanel.add(yearOfBirthField);
		fieldsPanel.add(monthList);
		fieldsPanel.add(daySpinner);

		// Configures the actionPanel and adds associated elements
		calculateAge = new JButton("Calculate Age");
		actionPanel.add(calculateAge);
		getRootPane().setDefaultButton(calculateAge);
		calculateAge.addActionListener(this); // adds an action listener to
												// this button

		// Configures the displayPanel and adds associated elements
		displayPanel.setLayout(new FlowLayout(FlowLayout.LEADING, 0, 9));
		displayPanel.setPreferredSize(new Dimension(420, 50));
		displayPanel.setBackground(Color.LIGHT_GRAY);
		displayPanel.add(new MyLabel(OUTPUT, OUTPUT_FONT));
		outputAge = new MyLabel(null, OUTPUT_FONT);
		displayPanel.add(outputAge);

		// Adds the panels to the contentPane
		contentPane.add(fieldsPanel, BorderLayout.NORTH);
		contentPane.add(actionPanel, BorderLayout.CENTER);
		contentPane.add(displayPanel, BorderLayout.SOUTH);
	}

	/**
	 * This method is invoked when a button is pressed.
	 */
	public void actionPerformed(ActionEvent e) {
		try {
			int year = Integer.parseInt(yearOfBirthField.getText());
			int month = monthList.getSelectedIndex();
			int day = Integer.parseInt(daySpinner.getValue().toString());
	
			GregorianCalendar today = new GregorianCalendar();
			GregorianCalendar birthdate = new GregorianCalendar(year, month, day);
			
			int ageInYears = getAge(today, birthdate);
			
			if (today.get(Calendar.MONTH) == birthdate.get(Calendar.MONTH)
					&& today.get(Calendar.DATE) == birthdate.get(Calendar.DATE)) {
				this.outputAge.setText(ageInYears + ", HAPPY BIRTHDAY!");
			}
			else {
				this.outputAge.setText(Integer.toString(ageInYears));
			}
			
		} catch (NumberFormatException msg) {
			this.outputAge.setText("INVALID YEAR INPUT");
		}
	}

	/**
	 * Calculates how many years difference there are between two dates.
	 * @param today Today's date.
	 * @param birthdate The comparison date (i.e. a birthdate)
	 * @return the number of years difference.
	 */
	private int getAge(GregorianCalendar today, GregorianCalendar birthdate) {

		int years = today.get(Calendar.YEAR) - birthdate.get(Calendar.YEAR);
		
		if (today.get(Calendar.MONTH) < birthdate.get(Calendar.MONTH)) {
			years--;
		}
		if (today.get(Calendar.MONTH) == birthdate.get(Calendar.MONTH)
				&& today.get(Calendar.DATE) < birthdate.get(Calendar.DATE)) {
			years--;
		}

		return years;
	}

	/**
	 * Inner class for easy creation of JLabels.
	 */
	private class MyLabel extends JLabel {

		private static final long serialVersionUID = 3821937932L;

		/**
		 * Sets the JLabel text based on an input string and centers the label.
		 * 
		 * @param text
		 *            Label text.
		 */
		public MyLabel(String text) {
			super(text);
			setHorizontalAlignment(SwingConstants.CENTER);
		}

		/**
		 * Overloaded constructor to allow for more customization of labels.
		 * 
		 * @param text
		 *            Label text.
		 * @param font
		 *            Label's font.
		 */
		public MyLabel(String text, Font font) {
			super(text);
			setFont(font);
		}
	}
}