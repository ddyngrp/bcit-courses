import java.awt.*;
import javax.swing.*;
import javax.accessibility.*;

/* Corner.java is used by AccessibleScrollDemo.java. */

public class Corner extends JComponent
                            implements Accessible {
    protected void paintComponent(Graphics g) {
        // Fill me with dirty brown/orange.
        g.setColor(new Color(230, 163, 4));
        g.fillRect(0, 0, getWidth(), getHeight());
    }

    public AccessibleContext getAccessibleContext() {
        if (accessibleContext == null) {
            accessibleContext = new AccessibleCorner();
        }
        return accessibleContext;
    }

    protected class AccessibleCorner extends AccessibleJComponent {
        //Inherit everything, override nothing.
    }
}
