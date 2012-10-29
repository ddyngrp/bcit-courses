import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class AnimationDemoUsingThread extends JFrame {
  public AnimationDemoUsingThread() {
    // Create a MovingMessagePanel for displaying a moving message
    add(new MovingMessagePanel("message moving?"));
  }

  /** Main method */
  public static void main(String[] args) {
    JFrame frame = new AnimationDemoUsingThread();
    frame.setTitle("AnimationDemoUsingThread");
    frame.setLocationRelativeTo(null); // Center the frame
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(280, 100);
    frame.setVisible(true);
  }

  // Displaying a moving message
  class MovingMessagePanel extends JPanel implements Runnable {
    private String message = "Welcome to Java";
    private int xCoordinate = 0;
    private int yCoordinate = 20;

    public MovingMessagePanel(String message) {
      this.message = message;

      // Create a timer
      Thread thread = new Thread(this);
      thread.start();
    }

    public void run() {
      try {
        while (true) {
          repaint();
          Thread.sleep(10);
        }
      }
      catch (InterruptedException ex) {
        ex.printStackTrace();
      }
    }

    /** Paint message */
    public void paintComponent(Graphics g) {
      super.paintComponent(g);

      if (xCoordinate > getWidth()) {
        xCoordinate = -20;
      }
      xCoordinate += 5;
      g.drawString(message, xCoordinate, yCoordinate);
    }
  }
}
