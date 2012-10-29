import java.awt.Color;

import javax.swing.*;

public class PanelDemo extends JFrame {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		new PanelDemo();
	}
	
	private PanelDemo() {
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setBounds(100, 100, 200, 200);
		
		JPanel panel = new JPanel();
		add(panel);
		
		panel.setBackground(new Color(200, 200, 255));
		panel.setBorder(BorderFactory.createTitledBorder("Titled Border"));
		
		setVisible(true);
	}

}
