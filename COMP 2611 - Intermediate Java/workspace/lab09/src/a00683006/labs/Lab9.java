/**
 * Project: lab09
 * File: Lab9.java
 * Date: 12-Nov-07
 * Time: 4:48:44 PM
 */
package a00683006.labs;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import java.io.*;
import java.beans.*;

import a00683006.data.*;
import a00683006.util.*;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class Lab9 {
	private static final long serialVersionUID = 9128739837L;
	private JMenu fileMenu, sortMenu, helpMenu;
	private JMenuItem fileOrig, fileImport, fileExport, fileExit,
					  sortName, sortEmail,
					  helpAbout;
	private JTextArea jtaGuestList;
	private MyFrame jfContainer;
	private ArrayList<Guest> guestList;

	public Lab9() {
		JPanel jpMain = new JPanel();
		jfContainer = new MyFrame();
		jfContainer.getContentPane().add(jpMain);
		
		jpMain.setLayout(new GridLayout());
		
		JScrollPane scrollPane = new JScrollPane(jtaGuestList = new JTextArea());
		jpMain.add(scrollPane);
		jtaGuestList.setEditable(false);
		
		createMenu();
		originalList();
	}
	
	public static void main(String[] args) {
		Lab9 lab = new Lab9();
		lab.jfContainer.setVisible(true);
	}
	
	private void createMenu() {
		JMenuBar jmbMenu = new JMenuBar();
		jfContainer.setJMenuBar(jmbMenu);
		
		fileMenu = new JMenu("File");
		sortMenu = new JMenu("Sort");
		helpMenu = new JMenu("Help");
		
		fileMenu.setMnemonic('F');
		sortMenu.setMnemonic('S');
		helpMenu.setMnemonic('H');
		
		jmbMenu.add(fileMenu);
		jmbMenu.add(sortMenu);
		jmbMenu.add(helpMenu);
		
		fileMenu.add(fileOrig = new JMenuItem("Original List", 'O'));
		fileMenu.addSeparator();
		fileMenu.add(fileImport = new JMenuItem("Import", 'I'));
		fileMenu.add(fileExport = new JMenuItem("Export", 'E'));
		fileMenu.addSeparator();
		fileMenu.add(fileExit = new JMenuItem("Exit", 'X'));
		
		sortMenu.add(sortName = new JMenuItem("By Last Name", 'L'));
		sortMenu.add(sortEmail = new JMenuItem("By Email Address", 'M'));
		
		helpMenu.add(helpAbout = new JMenuItem("About", 'A'));
		
		fileOrig.setAccelerator(
				KeyStroke.getKeyStroke(KeyEvent.VK_O, ActionEvent.CTRL_MASK));
		fileImport.setAccelerator(
				KeyStroke.getKeyStroke(KeyEvent.VK_I, ActionEvent.CTRL_MASK));
		fileExport.setAccelerator(
				KeyStroke.getKeyStroke(KeyEvent.VK_E, ActionEvent.CTRL_MASK));
		fileExit.setAccelerator(
				KeyStroke.getKeyStroke(KeyEvent.VK_Q, ActionEvent.CTRL_MASK));
		
		sortName.setAccelerator(
				KeyStroke.getKeyStroke(KeyEvent.VK_L, ActionEvent.CTRL_MASK));
		sortEmail.setAccelerator(
				KeyStroke.getKeyStroke(KeyEvent.VK_M, ActionEvent.CTRL_MASK));

		helpAbout.setAccelerator(
				KeyStroke.getKeyStroke(KeyEvent.VK_A, ActionEvent.CTRL_MASK));
		
		fileOrig.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				originalList();
			}
		});
		fileImport.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					importXML();	
				}
				catch (IOException error) {
					// don't say anything
				}
			}
		});
		fileExport.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					exportXML();	
				}
				catch (IOException error) {
					// don't say anything
				}
			}
		});
		fileExit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});
		
		sortName.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				sortByLastName();
			}
		});
		sortEmail.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				sortByEmail();
			}
		});

		helpAbout.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				messageDialogue("About Lab 9", "Lab 9\nBy Steffen L. Norgren A00683006");
			}
		});
	}
	
	private void originalList() {
		ArrayList<String> guestFile = new ReadFile().textFile("Guests.txt");
		guestList = new ArrayList<Guest>();
		
		for (String guest : guestFile) {
			try {
				guestList.add(new Guest(guest));
			}
			catch (DataException ex) {
				// Ignoring errors
			}
		}	
		
		jtaGuestList.setText("Original List:\n" + CollectionUtil.returnText(guestList));
	}
	
	private void sortByLastName() {
		GuestSorter.ByLastName byLastNameComparator = new GuestSorter.ByLastName();
		Collections.sort(guestList, byLastNameComparator);
		
		jtaGuestList.setText("Guests sorted by Last Name:\n"
				+ CollectionUtil.returnText(guestList));
	}
	
	private void sortByEmail() {
		GuestSorter.ByEmailAddress byEmailComparator = new GuestSorter.ByEmailAddress();
		Collections.sort(guestList, byEmailComparator);
		
		jtaGuestList.setText("Guests sorted by Email Address:\n"
				+ CollectionUtil.returnText(guestList));
	}
	
	private void exportXML() throws IOException {
		XMLEncoder encodeXML = new XMLEncoder(
				new BufferedOutputStream(
						new FileOutputStream("Lab9.xml")));
		
		encodeXML.writeObject(guestList);
		encodeXML.close();
		messageDialogue("The guests have been exported.");
	}
	
	private void importXML() throws IOException {
		XMLDecoder decodeXML = new XMLDecoder(
				new BufferedInputStream(
						new FileInputStream("Lab9.xml")));

		ArrayList<Guest> guestList = (ArrayList<Guest>)decodeXML.readObject();
		decodeXML.close();
		
		jtaGuestList.setText("Imported Data:\n"
				+ CollectionUtil.returnText(guestList));
	}
	
	private void messageDialogue(String message) {
		JOptionPane.showMessageDialog(null, message);
	}
	
	private void messageDialogue(String title, String message) {
		JOptionPane.showMessageDialog(null, message, title, JOptionPane.INFORMATION_MESSAGE);
	}
	
	private class MyFrame extends JFrame {
		private static final long serialVersionUID = 891273981273L;
		
		/**
		 * Default frame.
		 */
		public MyFrame() {
			super("Lab 9");
			setSize(800,200);
			setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			setLocationRelativeTo(null);
		}
	}
}