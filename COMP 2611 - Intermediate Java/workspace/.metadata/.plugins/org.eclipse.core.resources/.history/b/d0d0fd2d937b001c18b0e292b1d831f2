//v 1.3

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

// This example demonstrates the use of JButton, JTextField
// and JLabel.
public class CelsiusConverter2 implements ActionListener {
    JFrame converterFrame;
    JPanel converterPanel;
    JTextField tempCelsius;
    JLabel celsiusLabel, fahrenheitLabel;
    JButton convertTemp;

    // Constructor
    public CelsiusConverter2() {
	// Create the frame and container.
	converterFrame = new JFrame("Convert Celsius to Fahrenheit");
	converterPanel = new JPanel();
	converterPanel.setLayout(new GridLayout(2, 2));
	
	// Add the widgets.
	addWidgets();

	// Add the panel to the frame.
	converterFrame.getContentPane().add(converterPanel, BorderLayout.CENTER);

        // Exit when the window is closed.
        converterFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 

	// Show the converter.
	converterFrame.pack();
	converterFrame.setVisible(true);
    }

    // Create and add the widgets for converter.
    private void addWidgets() {
	// Create widgets.
	
	ImageIcon icon = new ImageIcon("images/convert.gif", "Convert temperature");
	tempCelsius = new JTextField(2);
	celsiusLabel = new JLabel("Celsius", SwingConstants.LEFT);
	convertTemp = new JButton(icon);
	fahrenheitLabel = new JLabel("Fahrenheit", SwingConstants.LEFT);

	celsiusLabel.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));
	fahrenheitLabel.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));

	// Listen to events from Convert button.
	convertTemp.addActionListener(this);

	// Add widgets to container.
	converterPanel.add(tempCelsius);
	converterPanel.add(celsiusLabel);
	converterPanel.add(convertTemp);
	converterPanel.add(fahrenheitLabel);
    }

    // Implementation of ActionListener interface.
    public void actionPerformed(ActionEvent event) {
	// Parse degrees Celsius as a double and convert to Fahrenheit.
        int tempFahr = (int)((Double.parseDouble(tempCelsius.getText())) 
                           * 1.8 + 32);

	// Set fahrenheitLabel to new value and set font color based on the temperature.
	if (tempFahr <= 32) {
	    fahrenheitLabel.setText("<html><Font Color=blue>" + tempFahr + "&#176 </Font><Font Color=black> Fahrenheit</font></html>");
	} else if (tempFahr <= 80) {
	    fahrenheitLabel.setText("<html><Font Color=green>" + tempFahr + "&#176 </Font><Font Color=black> Fahrenheit </Font></html>");
	} else {
	    fahrenheitLabel.setText("<html><Font Color=red>" + tempFahr + "&#176 </Font><Font Color=black> Fahrenheit</Font></html>");
	}
    }

    // main method
    public static void main(String[] args) {
	// set the look and feel
	try {
	    UIManager.setLookAndFeel(
		UIManager.getCrossPlatformLookAndFeelClassName());
	} catch(Exception e) {}

	CelsiusConverter2 converter = new CelsiusConverter2();
	
    }
}
