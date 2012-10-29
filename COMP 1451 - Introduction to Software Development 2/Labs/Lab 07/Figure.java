
/**
 * Write a description of class Figure here.
 * 
 * @author Steffen L. Norgren
 * @version August 1, 2007
 */
public abstract class Figure
{
    private int xPosition;
    private int yPosition;
    private String color;
    private boolean isVisible;

    /**
     * Constructor for objects of class Figure
     */
    public Figure(int newXPosition, int newYPosition,
                  String newColor, boolean newIsVisible)
    {
        xPosition = newXPosition;
        yPosition = newYPosition;
        color = newColor;
        isVisible = newIsVisible;
    }
    
    abstract public void draw();
    
    /**
     * Make this Figure visible. If it was already visible, do nothing.
     */
    public void makeVisible()
    {
        isVisible = true;
        draw();
    }
    
    /**
     * Make this Figure invisible. If it was already invisible, do nothing.
     */
    public void makeInvisible()
    {
        erase();
        isVisible = false;
    }
    
    /**
     * Accessor for isVisible
     */
    public boolean getIsVisible()
    {
        return isVisible;
    }

    /**
     * Accessor for color
     */
    public String getColor()
    {
        return color;
    }

    /**
     * Accessor for xPosition
     */
    public int getXPosition()
    {
        return xPosition;
    }
    
    /**
     * Accessor for yPosition
     */
    public int getYPosition()
    {
        return yPosition;
    }
    
    /**
     * Change the color. Valid colors are "red", "yellow", "blue", "green",
     * "magenta" and "black".
     */
    public void changeColor(String newColor)
    {
        color = newColor;
        draw();
    }
    
    /**
     * Move the Figure a few pixels to the right.
     */
    public void moveRight()
    {
        moveHorizontal(20);
    }

    /**
     * Move the Figure a few pixels to the left.
     */
    public void moveLeft()
    {
        moveHorizontal(-20);
    }

    /**
     * Move the Figure a few pixels up.
     */
    public void moveUp()
    {
        moveVertical(-20);
    }

    /**
     * Move the Figure a few pixels down.
     */
    public void moveDown()
    {
        moveVertical(20);
    }

    /**
     * Move the Figure horizontally by 'distance' pixels.
     */
    public void moveHorizontal(int distance)
    {
        erase();
        xPosition += distance;
        draw();
    }

    /**
     * Move the Figure vertically by 'distance' pixels.
     */
    public void moveVertical(int distance)
    {
        erase();
        yPosition += distance;
        draw();
    }

    /**
     * Slowly move the Figure horizontally by 'distance' pixels.
     */
    public void slowMoveHorizontal(int distance)
    {
        int delta;

        if(distance < 0) 
        {
            delta = -1;
            distance = -distance;
        }
        else 
        {
            delta = 1;
        }

        for(int i = 0; i < distance; i++)
        {
            xPosition += delta;
            draw();
        }
    }

    /**
     * Slowly move the Figure vertically by 'distance' pixels.
     */
    public void slowMoveVertical(int distance)
    {
        int delta;

        if(distance < 0) 
        {
            delta = -1;
            distance = -distance;
        }
        else 
        {
            delta = 1;
        }

        for(int i = 0; i < distance; i++)
        {
            yPosition += delta;
            draw();
        }
    }
    
    /**
     * Erase the Figure on screen.
     */
    public void erase()
    {
        if(isVisible) {
            Canvas canvas = Canvas.getCanvas();
            canvas.erase(this);
        }
    }
}
