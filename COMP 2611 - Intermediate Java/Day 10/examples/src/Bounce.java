// Bounce.java

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

public class Bounce extends JFrame {  
   private Button btnStart = new Button("Start");
   private Button btnClose = new Button("Close");
   private Canvas canvas;
   private Color[] COLORS = { Color.BLACK, Color.BLUE, Color.CYAN,
			Color.DARK_GRAY, Color.GRAY, Color.GREEN, Color.LIGHT_GRAY,
			Color.MAGENTA, Color.ORANGE, Color.PINK, Color.RED, Color.WHITE,
			Color.YELLOW };

	private static int index;

   public Bounce(){
		super("Bounce");

		setDefaultCloseOperation(EXIT_ON_CLOSE);
		canvas = new Canvas();
		add(canvas, BorderLayout.CENTER);

		Panel p = new Panel();
		p.add(btnStart);
		p.add(btnClose);
		add(p, BorderLayout.SOUTH);

		btnStart.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (index == COLORS.length) {
					index = 0;
				}
				Ball b = new Ball(canvas, COLORS[index]);
				b.bounce();
				index++;
			}
		});

		btnClose.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});
   }
   
   public static void main(String[] args){
      Bounce bounce = new Bounce();
	  bounce.setSize(300, 200);
	  bounce.setVisible(true);  
   }
}
