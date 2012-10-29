import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

public class AgeCalculator extends JFrame {

	private JTextField yearOfBirthField;

	private JTextField ageField;

	private JComboBox monthField;

	private JComboBox dayField;

	private final static String[] MONTHS = { "January", "February", "March", "April", "May", "June", "July",
			"August", "September", "October", "November", "December" };

	private final static String[] DAYS = { "1", "2", "3", "4", "5", "6", "7",
			"8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18",
			"19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
			"30", "31" };

	public static void main(String[] args) {
		AgeCalculator lab = new AgeCalculator();
		lab.create();
		lab.setVisible(true);
	}

	public AgeCalculator() {
		super("Age Calculator");
		create();
	}

	void create() {
		setDefaultCloseOperation(EXIT_ON_CLOSE);

		setBounds(500, 200, 200, 140);

		Container contentPane = getContentPane();

		JPanel fieldsPanel = new JPanel();

		yearOfBirthField = new JTextField(4);
		monthField = new JComboBox(MONTHS);
		dayField = new JComboBox(DAYS);

		fieldsPanel.setLayout(new GridLayout(2, 3));
		fieldsPanel.add(new MyLabel("Year"));
		fieldsPanel.add(new MyLabel("Month"));
		fieldsPanel.add(new MyLabel("Day"));
		fieldsPanel.add(yearOfBirthField);
		fieldsPanel.add(monthField);
		fieldsPanel.add(dayField);
		contentPane.add(fieldsPanel, BorderLayout.NORTH);

		JPanel actionPanel = new JPanel();
		JButton calculateAge = new JButton("Calculate Age");
		actionPanel.add(calculateAge);
		contentPane.add(actionPanel, BorderLayout.CENTER);
		calculateAge.addActionListener(new CalculateAction());
		getRootPane().setDefaultButton(calculateAge);

		ageField = new JTextField();
		contentPane.add(new JPanel().add(ageField), BorderLayout.SOUTH);
	}

	// inner classes
	private class CalculateAction implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			try {
				int yearOfBirth = Integer.parseInt(yearOfBirthField.getText());
				int monthOfBirth = monthField.getSelectedIndex();
				int dayOfBirth = dayField.getSelectedIndex();
				int age = calAge(yearOfBirth, monthOfBirth, dayOfBirth);
				String text = Integer.toString(age);
				ageField.setText(text);
				yearOfBirthField.selectAll();
			} catch (NumberFormatException nfe) {
				JOptionPane.showMessageDialog(new JFrame(),
						"Invalid date of birth", "Error",
						JOptionPane.ERROR_MESSAGE);
			}
		}

		public int calAge(int year, int month, int day) {
			boolean add = false;
			GregorianCalendar cal = new GregorianCalendar();
			int thisYear = cal.get(Calendar.YEAR);
			int thisMonth = cal.get(Calendar.MONTH);
			int today = cal.get(Calendar.DAY_OF_MONTH);

			if (month > thisMonth) {
				add = true;
			}

			if (add) {
				return (thisYear - year) - 1;
			} else {
				return (thisYear - year);
			}
		}

	}

	private class MyLabel extends JLabel {
		public MyLabel(String text) {
			super(text);
			setHorizontalAlignment(SwingConstants.CENTER);
		}
	}

}
