/*
 * Used by BoxLayoutDemo.java.
*/

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/** A rectangle that has a fixed size. */
class BLDComponent extends JComponent
                   implements MouseListener {
    private Color normalHue;
    private final Dimension preferredSize;
    private String name;
    private boolean restrictMaximumSize;
    private boolean printSize;

    public BLDComponent(float alignmentX, float hue,
                        int shortSideSize,
                        boolean restrictSize,
                        boolean printSize,
                        String name) {
        this.name = name;
        this.restrictMaximumSize = restrictSize;
        this.printSize = printSize;
        setAlignmentX(alignmentX);
        normalHue = Color.getHSBColor(hue, 0.4f, 0.85f);
        preferredSize = new Dimension(shortSideSize*2,
                                      shortSideSize);

        addMouseListener(this);
    }

    //The MouseListener interface requires that we define
    //mousePressed, mouseReleased, mouseEntered, mouseExited,
    //and mouseClicked.
    public void mousePressed(MouseEvent e) {
        int width = getWidth();
        float alignment = (float)(e.getX())
                        / (float)width;

        // Round to the nearest 1/10th.
        int tmp = Math.round(alignment * 10.0f);
        alignment = (float)tmp / 10.0f;

        setAlignmentX(alignment);
        revalidate(); // this GUI needs relayout
        repaint();
    }
    public void mouseReleased(MouseEvent e) { }
    public void mouseEntered(MouseEvent e) { }
    public void mouseExited(MouseEvent e) { }
    public void mouseClicked(MouseEvent e) { }

    /**
     * Our BLDComponents are completely opaque, so we override
     * this method to return true.  This lets the painting
     * system know that it doesn't need to paint any covered
     * part of the components underneath this component.  The
     * end result is possibly improved painting performance.
     */
    public boolean isOpaque() {
        return true;
    }

    public void paint(Graphics g) {
        int width = getWidth();
        int height = getHeight();
        float alignmentX = getAlignmentX();

        g.setColor(normalHue);
        g.fill3DRect(0, 0, width, height, true);

        /* Draw a vertical white line at the alignment point.*/
        // XXX: This code is probably not the best.
        g.setColor(Color.white);
        int x = (int)(alignmentX * (float)width) - 1;
        g.drawLine(x, 0, x, height - 1);

        /* Say what the alignment point is. */
        g.setColor(Color.black);
        g.drawString(Float.toString(alignmentX), 3, height - 3);

        if (printSize) {
            System.out.println("BLDComponent " + name + ": size is "
                               + width + "x" + height
                               + "; preferred size is "
                               + getPreferredSize().width + "x"
                               + getPreferredSize().height);
        }
    }

    public Dimension getPreferredSize() {
        return preferredSize;
    }

    public Dimension getMinimumSize() {
        return preferredSize;
    }

    public Dimension getMaximumSize() {
        if (restrictMaximumSize) {
            return preferredSize;
        } else {
            return super.getMaximumSize();
        }
    }

    public void setSizeRestriction(boolean restrictSize) {
        restrictMaximumSize = restrictSize;
    }
}
