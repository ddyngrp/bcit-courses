/*
 * ColorTransferHandler.java is used by the 1.4
 * DragColorDemo.java and DragColorTextFieldDemo examples.
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.datatransfer.*;
import java.awt.dnd.*;
import java.io.*;

/**
 * An implementation of TransferHandler that adds support for dropping
 * colors. Dropping a color on a component having this TransferHandler
 * changes the foreground or the background of the component to the dropped
 * color, according to the value of the changesForegroundColor property.
 */
class ColorTransferHandler extends TransferHandler {
    //The data type exported from JColorChooser.
    String mimeType = DataFlavor.javaJVMLocalObjectMimeType +
                        ";class=java.awt.Color";
    DataFlavor colorFlavor;
    private boolean changesForegroundColor = true;

    ColorTransferHandler() {
        //Try to create a DataFlavor for color.
        try {
            colorFlavor = new DataFlavor(mimeType);
        } catch (ClassNotFoundException e) { }
    }

    /**
     * Overridden to import a Color if it is available.
     * getChangesForegroundColor is used to determine whether
     * the foreground or the background color is changed.
     */
    public boolean importData(JComponent c, Transferable t) {
        if (hasColorFlavor(t.getTransferDataFlavors())) {
            try {
                Color col = (Color)t.getTransferData(colorFlavor);
                if (getChangesForegroundColor()) {
                    c.setForeground(col);
                } else {
                    c.setBackground(col);
                }
                return true;
            } catch (UnsupportedFlavorException ufe) {
                System.out.println("importData: unsupported data flavor");
            } catch (IOException ioe) {
                System.out.println("importData: I/O exception");
            }
        }
        return false;
    }

    /**
     * Does the flavor list have a Color flavor?
     */
    protected boolean hasColorFlavor(DataFlavor[] flavors) {
        if (colorFlavor == null) {
             return false;
        }

        for (int i = 0; i < flavors.length; i++) {
            if (colorFlavor.equals(flavors[i])) {
                return true;
            }
        }
        return false;
    }

    /**
     * Overridden to include a check for a color flavor.
     */
    public boolean canImport(JComponent c, DataFlavor[] flavors) {
        return hasColorFlavor(flavors);
    }

    protected void setChangesForegroundColor(boolean flag) {
        changesForegroundColor = flag;
    }

    protected boolean getChangesForegroundColor() {
        return changesForegroundColor;
    }
}
