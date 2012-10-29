import javax.swing.*;
import java.awt.event.*;

public class FlashingTextUsingTimer extends JApplet implements ActionListener {
  private JLabel jlblText = new JLabel("Welcome", JLabel.CENTER);
  private Timer timer = new Timer(2, this);

  public FlashingTextUsingTimer() {
    add(jlblText);
    timer.start();
  }

  /** Set the text on/off every 200 milliseconds */
  public void actionPerformed(ActionEvent e) {
    if (jlblText.getText() == null) {
      jlblText.setText("Welcome");
    }
    else {
      jlblText.setText(null);
    }
  }

  /** Main method */
  public static void main(String[] args) {
    JFrame frame = new JFrame("FlashingTextUsingTimer");
    frame.add(new FlashingTextUsingTimer());
    frame.setLocationRelativeTo(null); // Center the frame
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(200, 200);
    frame.setVisible(true);
  }

}
