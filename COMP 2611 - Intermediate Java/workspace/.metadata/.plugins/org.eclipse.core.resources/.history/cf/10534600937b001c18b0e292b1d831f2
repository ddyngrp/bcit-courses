import javax.swing.*;
import java.awt.*;

    
public class Test2 {
    JLabel label;

    public Test2() {
        JFrame f = new JFrame("Test2");
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); //1.3+
        createGUI(f);
        f.pack();
        f.setVisible(true);
    }

    void createGUI(JFrame f) {
        label = new JLabel("<html>The <em>last</em> word is <b>bold</b>.");
        Container c = f.getContentPane();
        //Use the content pane's default BorderLayout layout manager.
        c.add(label, BorderLayout.CENTER);
    }

    public static void main(String[] args) {
        new Test2();
    }
}
