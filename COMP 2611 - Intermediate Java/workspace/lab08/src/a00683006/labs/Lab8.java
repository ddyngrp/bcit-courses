/**
 * Project: lab08
 * File: Lab8.java
 * Date: 8-Nov-07
 * Time: 12:20:09 AM
 */
package a00683006.labs;

import java.awt.*;
import javax.swing.*;
import javax.swing.event.*;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class Lab8 extends JFrame {
	private static final long serialVersionUID = 91828379867L;
	private JTabbedPane tabbedPane;
	private JPanel colourPanel, fontPanel, imagePanel;
	private JList fontList;
	private JLabel fontLabel, image;
	private ListSelectionHandler fontControler;
	
	public static void main(String[] args) {
		Lab8 lab = new Lab8();
		lab.setVisible(true);
	}
	
	public Lab8()
	{
		setSize(400,300);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setLocationRelativeTo(null);
		
		JPanel topPanel = new JPanel();
		topPanel.setLayout( new BorderLayout() );
		getContentPane().add( topPanel );
		
		// Create the tab pages
		createColourPanel();
		createFontPanel();
		createImagePanel();
		
		// Create a tabbed pane
		tabbedPane = new JTabbedPane();
		tabbedPane.addTab( "Colours", colourPanel );
		tabbedPane.addTab( "Fonts", fontPanel );
		tabbedPane.addTab( "Image", imagePanel );
		topPanel.add( tabbedPane, BorderLayout.CENTER );
	}
	
	public void createColourPanel()
	{
		colourPanel = new JPanel();
		colourPanel.setLayout(new GridLayout(4,4));
		
		JPanel black = new JPanel();
		JPanel blue = new JPanel();
		JPanel cyan = new JPanel();
		JPanel darkGrey = new JPanel();
		JPanel grey = new JPanel();
		JPanel green = new JPanel();
		JPanel lightGrey = new JPanel();
		JPanel magenta = new JPanel();
		JPanel orange = new JPanel();
		JPanel pink = new JPanel();
		JPanel red = new JPanel();
		JPanel white = new JPanel();
		JPanel yellow = new JPanel();	
		
		black.setBackground(Color.BLACK);
		blue.setBackground(Color.BLUE);
		cyan.setBackground(Color.CYAN);
		darkGrey.setBackground(Color.DARK_GRAY);
		grey.setBackground(Color.GRAY);
		green.setBackground(Color.GREEN);
		lightGrey.setBackground(Color.LIGHT_GRAY);
		magenta.setBackground(Color.MAGENTA);
		orange.setBackground(Color.ORANGE);
		pink.setBackground(Color.PINK);
		red.setBackground(Color.RED);
		white.setBackground(Color.WHITE);
		yellow.setBackground(Color.YELLOW);
		
		colourPanel.add(black);
		colourPanel.add(blue);
		colourPanel.add(cyan);
		colourPanel.add(darkGrey);
		colourPanel.add(grey);
		colourPanel.add(green);
		colourPanel.add(lightGrey);
		colourPanel.add(magenta);
		colourPanel.add(orange);
		colourPanel.add(pink);
		colourPanel.add(red);
		colourPanel.add(white);
		colourPanel.add(yellow);
	}
	
	public void createFontPanel()
	{
		GraphicsEnvironment e = GraphicsEnvironment.getLocalGraphicsEnvironment();
		fontControler = new ListSelectionHandler();
		fontList = new JList(e.getAvailableFontFamilyNames());
		JScrollPane fontScrollPane = new JScrollPane(fontList);
		fontPanel = new JPanel();
		fontLabel = new JLabel("JAVA 0123456789", JLabel.CENTER);
		
		fontList.addListSelectionListener(fontControler);
		
		fontPanel.setLayout(new BorderLayout());
		fontList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		fontList.setSelectedIndex(0);
		fontScrollPane.setPreferredSize(new Dimension(155,0));
		
		fontPanel.add(fontScrollPane, BorderLayout.LINE_START);
		fontPanel.add(fontLabel, BorderLayout.CENTER);
		fontLabel.setFont(new Font(fontList.getSelectedValue().toString(),
				Font.PLAIN, 20));
	}
	
	public void createImagePanel()
	{
		image = new JLabel(new ImageIcon(getClass().getResource("BillGatesBorg.jpg")));
		imagePanel = new JPanel();

		imagePanel.setLayout(new BorderLayout());
		
		imagePanel.add(image, BorderLayout.CENTER);
	}
	
	private class ListSelectionHandler implements ListSelectionListener {
		public void valueChanged(ListSelectionEvent event) {
			fontLabel.setFont(new Font(fontList.getSelectedValue().toString(),
					Font.PLAIN, 20));
	    }
	}
}