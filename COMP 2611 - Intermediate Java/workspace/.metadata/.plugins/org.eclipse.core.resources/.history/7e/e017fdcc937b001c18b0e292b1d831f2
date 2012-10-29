import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.*;
import javax.swing.colorchooser.*;

/* Used by ColorChooserDemo2.java. */
public class CrayonPanel extends AbstractColorChooserPanel
                         implements ActionListener {
    JToggleButton redCrayon;
    JToggleButton yellowCrayon;
    JToggleButton greenCrayon;
    JToggleButton blueCrayon;

    public void updateChooser() {
        Color color = getColorFromModel();
        if (Color.red.equals(color)) {
            redCrayon.setSelected(true);
        } else if (Color.yellow.equals(color)) {
            yellowCrayon.setSelected(true);
        } else if (Color.green.equals(color)) {
            greenCrayon.setSelected(true);
        } else if (Color.blue.equals(color)) {
            blueCrayon.setSelected(true);
        }
    }

    protected JToggleButton createCrayon(String name,
                                         Border normalBorder) {
        JToggleButton crayon = new JToggleButton();
        crayon.setActionCommand(name);
        crayon.addActionListener(this);

        //Set the image or, if that's invalid, equivalent text.
        ImageIcon icon = createImageIcon("images/" + name + ".gif");
        if (icon != null) {
            crayon.setIcon(icon);
            crayon.setToolTipText("The " + name + " crayon");
            crayon.setBorder(normalBorder);
        } else {
            crayon.setText("Image not found. This is the "
                           + name + " button.");
            crayon.setFont(crayon.getFont().deriveFont(Font.ITALIC));
            crayon.setHorizontalAlignment(JButton.HORIZONTAL);
            crayon.setBorder(BorderFactory.createLineBorder(Color.BLACK));
        }

        return crayon;
    }

    protected void buildChooser() {
        setLayout(new GridLayout(0, 1));

        ButtonGroup boxOfCrayons = new ButtonGroup();
        Border border = BorderFactory.createEmptyBorder(4,4,4,4);

        redCrayon = createCrayon("red", border);
        boxOfCrayons.add(redCrayon);
        add(redCrayon);

        yellowCrayon = createCrayon("yellow", border);
        boxOfCrayons.add(yellowCrayon);
        add(yellowCrayon);

        greenCrayon = createCrayon("green", border);
        boxOfCrayons.add(greenCrayon);
        add(greenCrayon);

        blueCrayon = createCrayon("blue", border);
        boxOfCrayons.add(blueCrayon);
        add(blueCrayon);
    }

    /** Returns an ImageIcon, or null if the path was invalid. */
    protected static ImageIcon createImageIcon(String path) {
        java.net.URL imgURL = CrayonPanel.class.getResource(path);
        if (imgURL != null) {
            return new ImageIcon(imgURL);
        } else {
            System.err.println("Couldn't find file: " + path);
            return null;
        }
    }

    public void actionPerformed(ActionEvent e) {
        Color newColor = null;
        String command = ((JToggleButton)e.getSource()).getActionCommand();
        if ("green".equals(command))
            newColor = Color.green;
        else if ("red".equals(command))
            newColor = Color.red;
        else if ("yellow".equals(command))
            newColor = Color.yellow;
        else if ("blue".equals(command))
            newColor = Color.blue;
        getColorSelectionModel().setSelectedColor(newColor);
    }

    public String getDisplayName() {
        return "Crayons";
    }

    public Icon getSmallDisplayIcon() {
        return null;
    }

    public Icon getLargeDisplayIcon() {
        return null;
    }
}
