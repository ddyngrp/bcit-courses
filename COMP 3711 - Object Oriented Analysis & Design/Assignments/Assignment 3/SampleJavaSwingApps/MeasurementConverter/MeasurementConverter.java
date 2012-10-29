import java.awt.*;
import java.awt.event.*;
import java.text.NumberFormat;
import java.util.*;
import javax.swing.*;

public class MeasurementConverter extends JFrame implements ActionListener {

	private JComboBox feetField;

	private JComboBox inchesField;

	private JTextField resultField;

	private NumberFormat decimalFormatter;

	public static void main(String[] args) {
		MeasurementConverter lab = new MeasurementConverter();
		lab.create();
		lab.setVisible(true);
	}

	MeasurementConverter() {
		super("Measurement Converter");
		create();

		decimalFormatter = NumberFormat.getNumberInstance();
		decimalFormatter.setMinimumFractionDigits(1);
		decimalFormatter.setMaximumFractionDigits(1);
	}

	void create() {
		setDefaultCloseOperation(EXIT_ON_CLOSE);

		setLocationRelativeTo(null);
		setSize(260, 175);

		Container contentPane = getContentPane();

		JPanel fieldsPanel = new JPanel();

		Integer[] feet = new Integer[10];
		for (int i = 0; i < feet.length; i++) {
			feet[i] = new Integer(i);
		}
		feetField = new JComboBox(feet);
		Integer[] inches = new Integer[12];
		for (int i = 0; i < feet.length; i++) {
			inches[i] = new Integer(i);
		}
		inchesField = new JComboBox(inches);

		fieldsPanel.setLayout(new GridLayout(2, 2));
		fieldsPanel.add(new JLabel("Feet", SwingConstants.CENTER));
		fieldsPanel.add(new JLabel("Inches", SwingConstants.CENTER));
		fieldsPanel.add(feetField);
		fieldsPanel.add(inchesField);
		contentPane.add(fieldsPanel, BorderLayout.NORTH);

		JPanel actionPanel = new JPanel();
		JButton calculateButton = new JButton("Convert");
		actionPanel.add(calculateButton);
		contentPane.add(actionPanel, BorderLayout.CENTER);
		calculateButton.addActionListener(this);
		getRootPane().setDefaultButton(calculateButton);

		JPanel answerPanel = new JPanel();
		resultField = new JTextField();
		resultField.setPreferredSize(new Dimension(80, 24));
		answerPanel.add(resultField);
		answerPanel.add(new JLabel("Fathoms"));
		contentPane.add(answerPanel, BorderLayout.SOUTH);
	}

	public void actionPerformed(ActionEvent event) {
		try {
			int feet = feetField.getSelectedIndex();
			int inches = inchesField.getSelectedIndex();
			double hands = convert(feet, inches);
			resultField.setText(decimalFormatter.format(hands));
		} catch (NumberFormatException nfe) {
			JOptionPane
					.showMessageDialog(new JFrame(), "Invalid date of birth",
							"Error", JOptionPane.ERROR_MESSAGE);
		}
	}

	public double convert(int feet, int inches) {
		return (feet * 12 + inches) / 72.0;
	}
}
