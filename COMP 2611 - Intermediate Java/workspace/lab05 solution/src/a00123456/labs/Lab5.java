package a00123456.labs;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

public class Lab5 extends JFrame {

	private JTextField yearOfBirthField;

	private JLabel outputLabel;
	
	private final String OUTPUT = "Your age is: ";

	private JComboBox monthField;

	private JSpinner daySpinner;

	private final static String[] MONTHS = { "January", "February", "March", "April", "May", "June", "July",
			"August", "September", "October", "November", "December" };

	public static void main(String[] args) {
		Lab5 lab = new Lab5();
		lab.create();
		lab.setSize(300, 200);
		lab.setLocationRelativeTo(null);
		lab.setVisible(true);
		lab.setDefaultCloseOperation(EXIT_ON_CLOSE);
	}

	Lab5() {
		super("Calculate Age");
		create();
			
	}

	void create() {
		
		Container contentPane = getContentPane();

		JPanel fieldsPanel = new JPanel();

		yearOfBirthField = new JTextField(4);
		monthField = new JComboBox(MONTHS);
		daySpinner = new JSpinner(new SpinnerNumberModel(1, 1, 31, 1));

		fieldsPanel.setLayout(new GridLayout(2, 3));
		fieldsPanel.add(new MyLabel("Year"));
		fieldsPanel.add(new MyLabel("Month"));
		fieldsPanel.add(new MyLabel("Day"));
		fieldsPanel.add(yearOfBirthField);
		fieldsPanel.add(monthField);
		fieldsPanel.add(daySpinner);
		contentPane.add(fieldsPanel, BorderLayout.NORTH);

		JPanel actionPanel = new JPanel();
		
		JButton calculateAge = new JButton("Calculate Age");
		actionPanel.add(calculateAge);
		contentPane.add(actionPanel, BorderLayout.CENTER);
		getRootPane().setDefaultButton(calculateAge);
		
		JPanel displayPanel = new JPanel();
		displayPanel.setLayout(new GridLayout(1,1));
		displayPanel.setPreferredSize(new Dimension(300, 50));
		displayPanel.setBackground(Color.LIGHT_GRAY);
		
		outputLabel = new JLabel(OUTPUT);
		Font font = new Font("Arial Bold", Font.ITALIC, 24);
		outputLabel.setFont(font);
		outputLabel.setVerticalAlignment(SwingConstants.CENTER);
		displayPanel.add(outputLabel);

		/*ageField = new JTextField();*/
		contentPane.add(new JPanel().add(displayPanel), BorderLayout.SOUTH);
	}

	// inner classes
	private class MyLabel extends JLabel {
		public MyLabel(String text) {
			super(text);
			setHorizontalAlignment(SwingConstants.CENTER);
		}
	}
}