import java.awt.*;
import javax.swing.*;

public class ShowNoLayout extends JApplet {
  private JLabel jlbl =
    new JLabel("Resize the Window and Study No Layout",
      JLabel.CENTER);
  private JTextArea jta1 = new JTextArea("Text Area 1", 5, 10 );
  private JTextArea jta2 = new JTextArea("Text Area 2", 5, 10 );
  private JTextField jtf = new JTextField("TextField");
  private JPanel jp = new JPanel();
  private JButton jbt1 = new JButton("Cancel" );
  private JButton jbt2 = new JButton("Ok" );
  private GridBagLayout gbLayout;
  private GridBagConstraints gbConstraints;

  public ShowNoLayout() {
    // Set background color for the panel
    jp.setBackground(Color.red);

    // Specify no layout manager
    setLayout(null);

    // Add components to frame
    add(jlbl);
    add(jp);
    add(jta1);
    add(jta2);
    add(jtf);
    add(jbt1);
    add(jbt2);

    // Put components in the right place
    jlbl.setBounds(0, 10, 400, 40);
    jta1.setBounds(0, 50, 100, 100);
    jp.setBounds(100, 50, 200, 100);
    jta2.setBounds(300, 50, 100, 50);
    jtf.setBounds(300, 100, 100, 50);
    jbt1.setBounds(100, 150, 100, 50);
    jbt2.setBounds(200, 150, 100, 50);
  }

  public static void main(String[] args) {
    ShowNoLayout applet = new ShowNoLayout();
    JFrame frame = new JFrame();
    //EXIT_ON_CLOSE == 3
    frame.setDefaultCloseOperation(3);
    frame.setTitle("ShowNoLayout");
    frame.getContentPane().add(applet, BorderLayout.CENTER);
    applet.init();
    applet.start();
    frame.setSize(400,320);
    Dimension d = Toolkit.getDefaultToolkit().getScreenSize();
    frame.setLocation((d.width - frame.getSize().width) / 2, (d.height - frame.getSize().height) / 2);
    frame.setVisible(true);
  }
}
