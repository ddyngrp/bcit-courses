/*
 * DTPicture.java is used by the 1.4 DragPictureDemo.java example.
 */
import java.beans.*; 
import java.awt.*;
import java.awt.event.*;
import javax.accessibility.*;
import javax.swing.*;


//A subclass of Picture that supports Data Transfer.
class DTPicture extends Picture
                        implements MouseMotionListener {
    private MouseEvent firstMouseEvent = null;
    private static boolean installInputMapBindings = true;

    public DTPicture(Image image) {
        super(image);
        addMouseMotionListener(this);

        //Add the cut/copy/paste key bindings to the input map.
        //Note that this step is redundant if you are installing
        //menu accelerators that cause these actions to be invoked.
        //DragPictureDemo does not use menu accelerators and, since
        //the default value of installInputMapBindings is true,
        //the bindings are installed.  DragPictureDemo2 does use
        //menu accelerators and so calls setInstallInputMapBindings
        //with a value of false.  Your program would do one or the
        //other, but not both.
        if (installInputMapBindings) {
            InputMap imap = this.getInputMap();
            imap.put(KeyStroke.getKeyStroke("ctrl X"),
                TransferHandler.getCutAction().getValue(Action.NAME));
            imap.put(KeyStroke.getKeyStroke("ctrl C"),
                TransferHandler.getCopyAction().getValue(Action.NAME));
            imap.put(KeyStroke.getKeyStroke("ctrl V"),
                TransferHandler.getPasteAction().getValue(Action.NAME));
        }
        
        //Add the cut/copy/paste actions to the action map.
        //This step is necessary because the menu's action listener
        //looks for these actions to fire.
        ActionMap map = this.getActionMap();
        map.put(TransferHandler.getCutAction().getValue(Action.NAME),
                TransferHandler.getCutAction());
        map.put(TransferHandler.getCopyAction().getValue(Action.NAME),
                TransferHandler.getCopyAction());
        map.put(TransferHandler.getPasteAction().getValue(Action.NAME),
                TransferHandler.getPasteAction());
    }

    public void setImage(Image image) {
        this.image = image;
        this.repaint();
    }

    public void mousePressed(MouseEvent e) {
        //Don't bother to drag if there is no image.
        if (image == null) return;

        firstMouseEvent = e;
        e.consume();
    }

    public void mouseDragged(MouseEvent e) {
        //Don't bother to drag if the component displays no image.
        if (image == null) return;

        if (firstMouseEvent != null) {
            e.consume();

            //If they are holding down the control key, COPY rather than MOVE
            int ctrlMask = InputEvent.CTRL_DOWN_MASK;
            int action = ((e.getModifiersEx() & ctrlMask) == ctrlMask) ?
                  TransferHandler.COPY : TransferHandler.MOVE;

            int dx = Math.abs(e.getX() - firstMouseEvent.getX());
            int dy = Math.abs(e.getY() - firstMouseEvent.getY());
            //Arbitrarily define a 5-pixel shift as the
            //official beginning of a drag.
            if (dx > 5 || dy > 5) {
                //This is a drag, not a click.
                JComponent c = (JComponent)e.getSource();
                TransferHandler handler = c.getTransferHandler();
                //Tell the transfer handler to initiate the drag.
                handler.exportAsDrag(c, firstMouseEvent, action);
                firstMouseEvent = null;
            }
        }
    }

    public void mouseReleased(MouseEvent e) {
        firstMouseEvent = null;
    }

    public void mouseMoved(MouseEvent e) { }

    //This method is necessary because DragPictureDemo and
    //DragPictureDemo2 both use this class and DragPictureDemo
    //needs to have the input map bindings installed for
    //cut/copy/paste.  DragPictureDemo2 uses menu accelerators
    //and does not need to have the input map bindings installed.
    //Your program would use one approach or the other, but not
    //both.  The default for installInputMapBindings is true.
    public static void setInstallInputMapBindings(boolean flag) {
        installInputMapBindings = flag;
    }

    public static boolean getInstallInputMapBindingds() { //for completeness
        return installInputMapBindings;
    }
}
