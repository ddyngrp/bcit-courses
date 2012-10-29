/*
 * This is a 1.3 version (thanks to JFrame.EXIT_ON_CLOSE)
 * but could easily be converted to work in earlier releases.
 * There are many valid ways to implement the exercise.
 */

import javax.swing.*;
import java.awt.*;

public class SwingApp1 {
    JButton startButton, stopButton;
    JLabel label;

    public SwingApp1() {
        JFrame f = new JFrame("SwingApp1");
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); //1.3+
        createGUI(f);
        f.pack();
        f.setVisible(true);
    }

    void createGUI(JFrame f) {
        startButton = new JButton("Start");
        stopButton = new JButton("Stop");
        label = new JLabel("Press Start.", JLabel.CENTER);

        Container c = f.getContentPane();
        //Use the content pane's default BorderLayout layout manager.
        c.add(startButton, BorderLayout.WEST);
        c.add(stopButton, BorderLayout.EAST);
        c.add(label, BorderLayout.SOUTH);
    }

    public static void main(String[] args) {
        new SwingApp1();
    }
}
