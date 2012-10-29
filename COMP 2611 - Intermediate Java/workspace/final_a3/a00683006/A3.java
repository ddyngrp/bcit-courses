/**
 * Project: final_a3
 * File: A3.java
 * Date: 30-Nov-07
 * Time: 7:15:00 PM
 */
package a00683006;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class A3 {
	private MyFrame a3Container;
	private JPanel topPane, bottomPane;
	private JButton x1, x10, y1, y10, moveMe;

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		new A3();
	}
	
	private A3() {
		a3Container = new MyFrame();
		
		createUI();
		a3Container.setVisible(true);
	}
	
	private void createUI() {
		topPane = new JPanel();
		bottomPane = new JPanel();

		x1 = new JButton("x1");
		x10 = new JButton("x10");
		y1 = new JButton("y1");
		y10 = new JButton("y10");
		moveMe = new JButton("Move me!");
		
		a3Container.add(topPane, BorderLayout.NORTH);
		a3Container.add(bottomPane, BorderLayout.CENTER);
		bottomPane.setBackground(Color.LIGHT_GRAY);
		bottomPane.setLayout(null);
		
		topPane.add(x1);
		topPane.add(x10);
		topPane.add(y1);
		topPane.add(y10);
		
		bottomPane.add(moveMe);
		
		// xPosition, yPosition, width, height
		moveMe.setBounds(0, 0, 100, 30);
		
		x1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				moveButton(1,0);
			}
		});
		x10.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				moveButton(10,0);
			}
		});

		y1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				moveButton(0,1);
			}
		});
		y10.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				moveButton(0,10);
			}
		});
	}
	
	private void moveButton(int moveX, int moveY) {
		moveMe.setBounds(moveMe.getX()+moveX, moveMe.getY()+moveY, 100, 30);
	}
	
	private class MyFrame extends JFrame {
		private static final long serialVersionUID = 1287687621L;
		
		/**
		 * Default frame.
		 */
		public MyFrame() {
			setSize(300,300);
			setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			setLocationRelativeTo(null);
		}
	}
}
