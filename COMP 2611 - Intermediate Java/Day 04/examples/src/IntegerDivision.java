import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class IntegerDivision extends JApplet {
	// Text fields for Number 1, Number 2, and Result
	private JTextField jtfNum1, jtfNum2, jtfResult;

	// Create the "Divide" button
	private JButton jbtDiv = new JButton("Divide");

	public IntegerDivision() {
		// Panel p1 to hold text fields and labels
		JPanel p1 = new JPanel();
		p1.setLayout(new FlowLayout());
		p1.add(new JLabel("Number 1"));
		p1.add(jtfNum1 = new JTextField(3));
		p1.add(new JLabel("Number 2"));
		p1.add(jtfNum2 = new JTextField(3));
		p1.add(new JLabel("Result"));
		p1.add(jtfResult = new JTextField(4));
		jtfResult.setEditable(false);
		jtfResult.setHorizontalAlignment(SwingConstants.RIGHT);

		add(p1, BorderLayout.CENTER);
		add(jbtDiv, BorderLayout.SOUTH);

		// Register listener
		jbtDiv.addActionListener(new ActionListener() {
			/** Handle ActionEvent from the Divide button */
			public void actionPerformed(ActionEvent e) {
				// Get numbers
				int num1 = Integer.parseInt(jtfNum1.getText().trim());
				int num2 = Integer.parseInt(jtfNum2.getText().trim());

				int result = num1 / num2;

				// Set result in jtfResult
				jtfResult.setText(String.valueOf(result));
			}
		});
	}

	public static void main(String[] args) {
		// Create a frame
		JFrame frame = new JFrame("IntegerDivision");

		// Create an instance of the applet
		IntegerDivision applet = new IntegerDivision();

		// Add the applet instance to the frame
		frame.getContentPane().add(applet, BorderLayout.CENTER);

		// Display the frame
		frame.setSize(300, 300);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
}
