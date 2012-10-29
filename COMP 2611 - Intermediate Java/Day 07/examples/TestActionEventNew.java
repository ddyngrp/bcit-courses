import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class TestActionEventNew extends JFrame implements ActionListener {
  private JButton jbtOk = new JButton("OK");
  private JButton jbtCancel = new JButton("Cancel");

  public TestActionEventNew() {
    setLayout(new FlowLayout());

    add(jbtOk);
    add(jbtCancel);

    jbtOk.addActionListener(this);
    jbtCancel.addActionListener(this);
  }

  /** Main method */
  public static void main(String[] args) {
    TestActionEventNew frame = new TestActionEventNew();
    frame.setTitle("TestActionEventNew");
    frame.setLocationRelativeTo(null); // Center the frame
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(100, 80);
    frame.setVisible(true);
  }

  /** This method will be invoked when a button is clicked */
  public void actionPerformed(ActionEvent e) {
    System.out.println("The " + e.getActionCommand() + " button is "
      + "clicked at\n  " + new java.util.Date(e.getWhen()));
  }
}
