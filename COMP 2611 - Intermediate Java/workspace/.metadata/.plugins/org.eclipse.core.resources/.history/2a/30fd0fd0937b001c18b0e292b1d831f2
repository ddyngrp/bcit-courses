/*
 * ColorAndTextTransferHandler.java is used by the 1.4
 * DragColorDemo.java example.
 */

import java.io.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.datatransfer.*;
import java.awt.dnd.*;
import javax.swing.*;
import javax.swing.text.*;

/**
 * An implementation of TransferHandler that adds support for the
 * import of color and the import and export of text. Dropping a color 
 * on a component having this TransferHandler changes the foreground
 * of the component to the imported color.
 */
class ColorAndTextTransferHandler extends ColorTransferHandler {
    private DataFlavor stringFlavor = DataFlavor.stringFlavor;
    private JTextComponent source;
    private boolean shouldRemove;

    //Start and end position in the source text.
    //We need this information when performing a MOVE
    //in order to remove the dragged text from the source.
    Position p0 = null, p1 = null;

    //Get the flavors from the Transferable.
    //Is there a color flavor?  If so, set the foreground color.
    //Is there a string flavor?  If so, set the text property.
    public boolean importData(JComponent c, Transferable t) {
        JTextComponent tc = (JTextComponent)c;

        if (!canImport(c, t.getTransferDataFlavors())) {
            return false;
        }

        if (tc.equals(source) && (tc.getCaretPosition() >= p0.getOffset()) &&
                                 (tc.getCaretPosition() <= p1.getOffset())) {
            shouldRemove = false;
            return true;
        }

        if (hasStringFlavor(t.getTransferDataFlavors())) {
            try {
                String str = (String)t.getTransferData(stringFlavor);
                tc.replaceSelection(str);
                return true;
            } catch (UnsupportedFlavorException ufe) {
                System.out.println("importData: unsupported data flavor");
            } catch (IOException ioe) {
                System.out.println("importData: I/O exception");
            }
        }
        //The ColorTransferHandler superclass handles color.
        return super.importData(c, t);
    }

    //Create a Transferable implementation that contains the
    //selected text.
    protected Transferable createTransferable(JComponent c) {
        source = (JTextComponent)c;
        int start = source.getSelectionStart();
        int end = source.getSelectionEnd();
        Document doc = source.getDocument();
        if (start == end) {
            return null;
        }
        try {
            p0 = doc.createPosition(start);
            p1 = doc.createPosition(end);
        } catch (BadLocationException e) {
            System.out.println(
              "Can't create position - unable to remove text from source.");
        }
        shouldRemove = true;
        String data = source.getSelectedText();
        return new StringSelection(data);
    }

    public int getSourceActions(JComponent c) {
        return COPY_OR_MOVE;
    }

    //Remove the old text if the action is a MOVE.
    //However, we do not allow dropping on top of the selected text,
    //so in that case do nothing.
    protected void exportDone(JComponent c, Transferable data, int action) {
        if (shouldRemove && (action == MOVE)) {
            if ((p0 != null) && (p1 != null) &&
                (p0.getOffset() != p1.getOffset())) {
                try {
                    JTextComponent tc = (JTextComponent)c;
                    tc.getDocument().remove(
                       p0.getOffset(), p1.getOffset() - p0.getOffset());
                } catch (BadLocationException e) {
                    System.out.println("Can't remove text from source.");
                }
            }
        }
        source = null;
    }

    /**
     * Does flavors contain a color or string Transferable?
     */
    public boolean canImport(JComponent c, DataFlavor[] flavors) {
        if (hasStringFlavor(flavors)) {
            return true;
        }
        return super.canImport(c, flavors);
    }

    /**
     * Does the flavor list have a string flavor?
     */
    protected boolean hasStringFlavor(DataFlavor[] flavors) {
        for (int i = 0; i < flavors.length; i++) {
            if (stringFlavor.equals(flavors[i])) {
                return true;
            }
        }
        return false;
    }
}
