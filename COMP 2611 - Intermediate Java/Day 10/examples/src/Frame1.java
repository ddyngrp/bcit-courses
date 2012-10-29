import java.awt.BorderLayout;
import java.awt.Dimension;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class Frame1 extends JFrame {
  JPanel contentPane;
  BorderLayout borderLayout1 = new BorderLayout();

  public Frame1() {
    try {
      setDefaultCloseOperation(EXIT_ON_CLOSE);
      jbInit();
    } catch (Exception exception) {
      exception.printStackTrace();
    }
  }

  /**
   * Component initialization.
   *
   * @throws java.lang.Exception
   */
  private void jbInit() throws Exception {
    contentPane = (JPanel) getContentPane();
    contentPane.setLayout(borderLayout1);
    setSize(new Dimension(400, 300));
    setTitle("Frame Title");
  }
}