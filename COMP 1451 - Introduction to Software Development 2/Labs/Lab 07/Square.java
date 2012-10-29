import java.awt.*;

/**
 * A square that can be manipulated and that draws itself on a canvas.
 * 
 * @author  Michael Kolling and David J. Barnes
 * @version 2006.03.30
 */

public class Square extends Figure
{
    private int size;

    /**
     * Create a new square at default position with default color.
     */
    public Square()
    {
        super(60, 50, "red", false);
        size = 30;
    }

    /**
     * Change the size to the new size (in pixels). Size must be >= 0.
     */
    public void changeSize(int newSize)
    {
        erase();
        size = newSize;
        draw();
    }

    /**
     * Draw the square with current specifications on screen.
     */
    public void draw()
    {
        if(super.getIsVisible()) {
            Canvas canvas = Canvas.getCanvas();
            canvas.draw(this, super.getColor(),
                        new Rectangle(super.getXPosition(),
                                      super.getYPosition(),
                                      size, size));
            canvas.wait(10);
        }
    }
}
