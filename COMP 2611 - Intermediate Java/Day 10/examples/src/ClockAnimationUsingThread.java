import java.awt.*;
import javax.swing.*;

public class ClockAnimationUsingThread extends StillClock
    implements Runnable {
  public ClockAnimationUsingThread() {
    new Thread(this).start();
  }

  /** Repaint the clock every 1 second */
  public void run() {
    while (true) {
      setCurrentTime(); // Set new time
      repaint(); // Repaint clock
      try {
        Thread.sleep(1000);
      }
      catch (InterruptedException ex) {
      }
    }
  }

  /** Main method */
  public static void main(String[] args) {
    JFrame frame = new JFrame("ClockAnimationUsingThread");
    frame.add(new ClockAnimationUsingThread());
    frame.setLocationRelativeTo(null); // Center the frame
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(200, 200);
    frame.setVisible(true);
  }
}
