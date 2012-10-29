import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class TemperatureConverter extends JFrame 
								implements ActionListener{
	private JTextField inputField;

	private JTextField outputField;

	private ButtonGroup group;

	private JRadioButton rbCelsius, rbFahrenheit;

	public TemperatureConverter() {
		super("Temperature Converter");
		Container c = getContentPane();

		c.add(createMainPanel());
	}

	public JPanel createMainPanel() {
		JPanel panel = new JPanel();

		inputField = new JTextField(12);
		panel.add(inputField);
		JButton convert = new JButton("Convert");
		getRootPane().setDefaultButton(convert);
		convert.setMnemonic(KeyEvent.VK_C);
		panel.add(convert);
		outputField = new JTextField(12);
		panel.add(outputField);

		convert.addActionListener(this);

		rbCelsius = new JRadioButton("to Celsius");
		rbCelsius.setSelected(true);

		rbFahrenheit = new JRadioButton("to Fahrenheit");

		group = new ButtonGroup();
		group.add(rbCelsius);
		group.add(rbFahrenheit);

		panel.add(rbCelsius);
		panel.add(rbFahrenheit);

		return panel;
	}
	
	public void actionPerformed(ActionEvent event) {
		String text = inputField.getText();
		double inputValue = Double.parseDouble(text);
		if (rbCelsius.isSelected()) {
			double outputValue = convertF2C(inputValue);
			text = Double.toString(outputValue);
			outputField.setText(text);
		} else {
			double outputValue = convertC2F(inputValue);
			text = Double.toString(outputValue);
			outputField.setText(text);
		}

		inputField.requestFocus();
		inputField.selectAll();
	}

	public double convertF2C(double input) {
		double degreesCelsius = 5.0 / 9.0 * (input - 32);

		return degreesCelsius;
	}

	public double convertC2F(double input) {
		double degreesFahrenheit = 9.0 / 5.0 * input + 32;

		return degreesFahrenheit;
	}

	public static void main(String[] args) {
		TemperatureConverter app = new TemperatureConverter();
		app.setSize(200, 150);
		Toolkit theKit = app.getToolkit();
		Dimension windowSize = theKit.getScreenSize();
		app.setLocation((windowSize.width - 200) / 2,
				(windowSize.height - 150) / 2);
		app.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		app.setVisible(true);
	}
}
