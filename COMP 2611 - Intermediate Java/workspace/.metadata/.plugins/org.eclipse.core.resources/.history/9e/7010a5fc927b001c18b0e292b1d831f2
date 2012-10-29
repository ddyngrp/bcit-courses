//v 1.3
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.net.URL;

// This example demonstrates the use of JButton, JTextField
// and JLabel.
public class LunarPhases implements ActionListener {
    final static int NUM_IMAGES = 8;
    final static int START_INDEX = 3;

    ImageIcon[] images = new ImageIcon[NUM_IMAGES];
    JPanel mainPanel, selectPanel, displayPanel;

    JComboBox phaseChoices = null;
    JLabel phaseIconLabel = null;

    // Constructor
    public LunarPhases() {
	// Create the phase selection and display panels.
	selectPanel = new JPanel();
	displayPanel = new JPanel();

	// Add various widgets to the sub panels.
	addWidgets();

	// Create the main panel to contain the two sub panels.
	mainPanel = new JPanel();
	mainPanel.setLayout(new GridLayout(2,1,5,5));
	mainPanel.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));

	// Add the select and display panels to the main panel.
	mainPanel.add(selectPanel);
	mainPanel.add(displayPanel);
    }

    // Create and the widgets to select and display the phases of the moon.
    private void addWidgets() {
	// Get the images and put them into an array of ImageIcon.
	for (int i = 0; i < NUM_IMAGES; i++) {
	    String imageName = "images/image" + i + ".jpg";
	    System.out.println("getting image: " + imageName);
	    URL iconURL = ClassLoader.getSystemResource(imageName);

	    ImageIcon icon = new ImageIcon(iconURL);
	    images[i] = icon;
	}

	// Create label for displaying moon phase images and put a border around it.
	phaseIconLabel = new JLabel();
	phaseIconLabel.setHorizontalAlignment(JLabel.CENTER);
	phaseIconLabel.setVerticalAlignment(JLabel.CENTER);
	phaseIconLabel.setVerticalTextPosition(JLabel.CENTER);
	phaseIconLabel.setHorizontalTextPosition(JLabel.CENTER);
	phaseIconLabel.setBorder(BorderFactory.createCompoundBorder(
			    BorderFactory.createLoweredBevelBorder(),
			    BorderFactory.createEmptyBorder(5,5,5,5)));
	
	phaseIconLabel.setBorder(BorderFactory.createCompoundBorder(
			    BorderFactory.createEmptyBorder(0,0,10,0),
			    phaseIconLabel.getBorder()));

	// Create combo box with lunar phase choices.
	String[] phases = { "New", "Waxing Crescent", "First Quarter", 
			    "Waxing Gibbous", "Full", "Waning Gibbous", 
			    "Third Quarter", "Waning Crescent" };
	phaseChoices = new JComboBox(phases);
	phaseChoices.setSelectedIndex(START_INDEX);

	// Display the first image.
	phaseIconLabel.setIcon(images[START_INDEX]);
	phaseIconLabel.setText("");

    	// Add border around the select panel.
	selectPanel.setBorder(BorderFactory.createCompoundBorder(
		BorderFactory.createTitledBorder("Select Phase"), 
		BorderFactory.createEmptyBorder(5,5,5,5)));

    	// Add border around the display panel.
    	displayPanel.setBorder(BorderFactory.createCompoundBorder(
            BorderFactory.createTitledBorder("Display Phase"), 
            BorderFactory.createEmptyBorder(5,5,5,5)));

	// Add moon phases combo box to select panel and image label to displayPanel.
	selectPanel.add(phaseChoices);
	displayPanel.add(phaseIconLabel);

	// Listen to events from combo box.
	phaseChoices.addActionListener(this);
    }

    // Implementation of ActionListener interface.
    public void actionPerformed(ActionEvent event) {
	if ("comboBoxChanged".equals(event.getActionCommand())) {
	    // update the icon to display the new phase
	    phaseIconLabel.setIcon(images[phaseChoices.getSelectedIndex()]);
	}
    }

    // main method
    public static void main(String[] args) {
	// create a new instance of LunarPhases
	LunarPhases phases = new LunarPhases();

	// Create a frame and container for the panels.
	JFrame lunarPhasesFrame = new JFrame("Lunar Phases");

	// Set the look and feel.
	try {
	    UIManager.setLookAndFeel(
		UIManager.getCrossPlatformLookAndFeelClassName());
	} catch(Exception e) {}
	
	lunarPhasesFrame.setContentPane(phases.mainPanel);

        // Exit when the window is closed.
        lunarPhasesFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
	
	// Show the converter.
	lunarPhasesFrame.pack();
	lunarPhasesFrame.setVisible(true);
    }
}
