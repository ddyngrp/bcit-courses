import java.awt.*;

/**
 * A triangle that can be manipulated and that draws itself on a canvas.
 * 
 * @author  Michael Kolling and David J. Barnes
 * @version 2006.03.30
 */

public class Triangle extends Figure
{
    private int height;
    private int width;

    /**
     * Create a new triangle at default position with default color.
     */
    public Triangle()
    {
        super(50, 15, "green", false);
        height = 30;
        width = 40;
    }

    /**
     * Change the size to the new size (in pixels). Size must be >= 0.
     */
    public void changeSize(int newHeight, int newWidth)
    {
        erase();
        height = newHeight;
        width = newWidth;
        draw();
    }

    /**
     * Draw the triangle with current specifications on screen.
     */
    public void draw()
    {
        if(super.getIsVisible()) {
            Canvas canvas = Canvas.getCanvas();
            int[] xpoints = { super.getXPosition(), super.getXPosition()
                              + (width/2), super.getXPosition() - (width/2) };
            int[] ypoints = { super.getYPosition(), super.getYPosition()
                              + height, super.getYPosition() + height };
            canvas.draw(this, super.getColor(), new Polygon(xpoints, ypoints, 3));
            canvas.wait(10);
        }
    }
}
