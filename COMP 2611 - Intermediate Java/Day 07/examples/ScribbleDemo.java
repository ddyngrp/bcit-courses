import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class ScribbleDemo extends JFrame {
  public ScribbleDemo() {
    // Create a PaintPanel and add it to the frame
    add(new ScribblePanel(), BorderLayout.CENTER);
  }

  /** Main method */
  public static void main(String[] args) {
    ScribbleDemo frame = new ScribbleDemo();
    frame.setTitle("ScribbleDemo");
    frame.setLocationRelativeTo(null); // Center the frame
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(300, 300);
    frame.setVisible(true);
  }
}

// ScribblePanel for scribbling using the mouse
class ScribblePanel extends JPanel
    implements MouseListener, MouseMotionListener {
  final int CIRCLESIZE = 20; // Circle diameter used for erasing
  private Point lineStart = new Point(0, 0); // Line start point

  public ScribblePanel() {
    // Register listener for the mouse event
    addMouseListener(this);
    addMouseMotionListener(this);
  }

  public void mouseClicked(MouseEvent e) {
  }

  public void mouseEntered(MouseEvent e) {
  }

  public void mouseExited(MouseEvent e) {
  }

  public void mouseReleased(MouseEvent e) {
  }

  public void mousePressed(MouseEvent e) {
    lineStart.move(e.getX(), e.getY());
  }

  public void mouseDragged(MouseEvent e) {
    // Create a Graphics object for drawing
    Graphics g = getGraphics();

    if (e.isMetaDown()) { // Detect right button pressed
      // Erase the drawing using an oval
      g.setColor(getBackground());
      g.fillOval(e.getX() - (CIRCLESIZE / 2),
         e.getY() - (CIRCLESIZE / 2), CIRCLESIZE, CIRCLESIZE);
    }
    else {
      g.setColor(Color.black);
      g.drawLine(lineStart.x, lineStart.y,
        e.getX(), e.getY());
    }

    lineStart.move(e.getX(), e.getY());

    // Dispose this graphics context
    g.dispose();
  }

  public void mouseMoved(MouseEvent e) {
  }
}
