import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JFrame;
import java.awt.Container;
import java.awt.FlowLayout;

public class ShowFlowLayoutNew extends JFrame {
  public ShowFlowLayoutNew() {
    // Get the content pane of the frame
    Container container = getContentPane();

    // Set FlowLayout, aligned left with horizontal gap 10
    // and vertical gap 20 between components
    container.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 20));

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
    ShowFlowLayoutNew frame = new ShowFlowLayoutNew();
    frame.setTitle("ShowFlowLayoutNew");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(200, 200);
    frame.setVisible(true);
  }
}
