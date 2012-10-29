import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JFrame;
import java.awt.GridLayout;
import java.awt.Container;

public class ShowGridLayoutNew extends JFrame {
  public ShowGridLayoutNew() {
    // Get the content pane of the frame
    Container container = getContentPane();

    // Set GridLayout, 3 rows, 2 columns, and gaps 5 between
    // components horizontally and vertically
    container.setLayout(new GridLayout(3, 10, 5, 5));

    // Add labels and text fields to the frame
    container.add(new JLabel("First Name"));
    container.add(new JTextField(8));
    container.add(new JLabel("MI"));
    container.add(new JTextField(1));
    container.add(new JLabel("Last Name"));
    container.add(new JTextField(8));
  }

  /** Main method */
  public static void main(String[] args) {
    ShowGridLayoutNew frame = new ShowGridLayoutNew();
    frame.setTitle("ShowGridLayoutNew");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(200, 200);
    frame.setVisible(true);
  }
}
