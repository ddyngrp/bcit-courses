// MiniCalculator.java

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.plaf.metal.MetalLookAndFeel;

public class MiniCalculator extends JFrame implements ActionListener {
	char operator = 0;

	float storedValue = 0;

	boolean clearNext = false;

	JTextField display = new JTextField();

	JButton key1 = new JButton("1");

	JButton key2 = new JButton("2");

	JButton key3 = new JButton("3");

	JButton key4 = new JButton("4");

	JButton key5 = new JButton("5");

	JButton key6 = new JButton("6");

	JButton key7 = new JButton("7");

	JButton key8 = new JButton("8");

	JButton key9 = new JButton("9");

	JButton key0 = new JButton("0");

	JButton add = new JButton("+");

	JButton subtract = new JButton("-");

	JButton multiply = new JButton("*");

	JButton divide = new JButton("/");

	JButton equal = new JButton("=");

	JButton decimal = new JButton(".");

	JButton plusminus = new JButton("+/-");

	JButton clear = new JButton("C");

	JPanel blank = new JPanel();

	JPanel row1 = new JPanel();

	JPanel row2 = new JPanel();

	JPanel row3 = new JPanel();

	JPanel row4 = new JPanel();

	JPanel row5 = new JPanel();

	JPanel row6 = new JPanel();

	public MiniCalculator() {
		super("Java Calculator");
		Container c = getContentPane();

		c.setBackground(Color.gray);

		GridLayout layout = new GridLayout(6, 1, 5, 5);
		c.setLayout(layout);
		GridLayout grid = new GridLayout(1, 4, 5, 5);

		Font typeface = new Font("Helvetica", Font.BOLD, 25);
		row1.setLayout(grid);
		row1.setBackground(Color.gray);
		display.setBackground(Color.white);
		display.addActionListener(this);
		display.setFont(typeface);
		display.setEditable(false);
		row1.add(display);
		c.add(row1);

		Font typefaceButtons = new Font("Helvetica", Font.BOLD, 10);
		setFont(typefaceButtons);
		row2.setLayout(grid);
		row2.setBackground(Color.gray);
		key7.addActionListener(this);
		row2.add(key7);
		key8.addActionListener(this);
		row2.add(key8);
		key9.addActionListener(this);
		row2.add(key9);
		divide.addActionListener(this);
		row2.add(divide);
		c.add(row2);

		row3.setLayout(grid);
		row3.setBackground(Color.gray);
		key4.addActionListener(this);
		row3.add(key4);
		key5.addActionListener(this);
		row3.add(key5);
		key6.addActionListener(this);
		row3.add(key6);
		multiply.addActionListener(this);
		row3.add(multiply);
		c.add(row3);

		row4.setLayout(grid);
		row4.setBackground(Color.gray);
		key1.addActionListener(this);
		row4.add(key1);
		key2.addActionListener(this);
		row4.add(key2);
		key3.addActionListener(this);
		row4.add(key3);
		subtract.addActionListener(this);
		row4.add(subtract);
		c.add(row4);

		row5.setLayout(grid);
		row5.setBackground(Color.gray);
		key0.addActionListener(this);
		row5.add(key0);
		plusminus.addActionListener(this);
		Font typeface2 = new Font("Helvetica", Font.BOLD, 9);
		plusminus.setFont(typeface2);
		row5.add(plusminus);
		decimal.addActionListener(this);
		row5.add(decimal);
		add.addActionListener(this);
		row5.add(add);
		c.add(row5);

		row6.setLayout(grid);
		row6.setBackground(Color.gray);
		clear.addActionListener(this);
		row6.add(clear);
		row6.add(blank);
		row6.add(blank);
		equal.setEnabled(false);
		equal.addActionListener(this);
		row6.add(equal);
		c.add(row6);
	}

	public void actionPerformed(ActionEvent event) {
		String keyHit = event.getActionCommand();
		if (keyHit == "+/-") {
			float value = getValue(display.getText());
			value *= -1;
			clearDisplay();
			addToDisplay("" + value);
		} else
			switch (keyHit.charAt(0)) {
			case '+':
			case '-':
			case '*':
			case '/':
				equal.setEnabled(true);
				add.setEnabled(false);
				subtract.setEnabled(false);
				multiply.setEnabled(false);
				divide.setEnabled(false);
				storedValue = getValue(display.getText());
				operator = keyHit.charAt(0);
				clearNext = true;
				break;
			case '=':
				equal.setEnabled(false);
				add.setEnabled(true);
				subtract.setEnabled(true);
				multiply.setEnabled(true);
				divide.setEnabled(true);
				solveProblem();
				storedValue = getValue(display.getText());
				operator = 0;
				clearNext = true;
				break;
			case 'C':
				clearDisplay();
				operator = 0;
				storedValue = (float) 0;
				break;
			default:
				if (clearNext) {
					clearDisplay();
					clearNext = false;
				}
				addToDisplay(keyHit);
			}
	}

	public void solveProblem() {
		float currentValue = getValue(display.getText());
		switch (operator) {
		case '+':
			storedValue += currentValue;
			break;
		case '-':
			storedValue -= currentValue;
			break;
		case '*':
			storedValue *= currentValue;
			break;
		case '/':
			if (currentValue != 0)
				storedValue /= currentValue;
			else
				storedValue = 0;
			break;
		}
		clearDisplay();
		addToDisplay("" + storedValue);
		clearNext = true;
	}

	public void addToDisplay(String keyHit) {
		String newText = display.getText();
		if (keyHit == ".") {
			if (newText.indexOf(".") == -1)
				newText += ".";
		} else
			newText += keyHit;
		int newLength = newText.length();
		display.setText(newText);
	}

	public void clearDisplay() {
		display.setText("");
	}

	public float getValue(String argument) {
		if (argument.equals("."))
			argument = "0";
		Float f1 = Float.valueOf(argument);
		return f1.floatValue();
	}

	public static void main(String[] args) {
		MiniCalculator app = new MiniCalculator();
		app.setSize(300, 400);
		Toolkit theKit = app.getToolkit();
		Dimension windowSize = theKit.getScreenSize();
		app.setLocation((windowSize.width - app.getWidth()) / 2,
				(windowSize.height - app.getHeight()) / 2);
		app.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		app.setVisible(true);
	}
}
