
import java.io.OutputStream;
import javax.microedition.io.Connector;
import javax.microedition.io.file.FileConnection;
import net.rim.device.api.system.Bitmap;
import net.rim.device.api.ui.Field;
import net.rim.device.api.ui.FieldChangeListener;
import net.rim.device.api.ui.UiApplication;
import net.rim.device.api.ui.component.BitmapField;
import net.rim.device.api.ui.component.ButtonField;
import net.rim.device.api.ui.component.Dialog;
import net.rim.device.api.ui.component.LabelField;
import net.rim.device.api.ui.container.HorizontalFieldManager;
import net.rim.device.api.ui.container.MainScreen;

public final class ImageScreen extends MainScreen {
    /**A reference to the current screen for listeners.*/
    private ImageScreen imageScreen_;
    
    /**A counter for the number of snapshots taken.*/
    private static int counter_;
    
    /**The down-scaling ratio applied to the snapshot Bitmap.*/
    private static final int IMAGE_SCALING = 7;

    /**
    * Constructor.
    * @param raw A byte array representing an image.
    */
    public ImageScreen(final byte[] raw) {
        //A reference to this object, to be used in listeners.
        imageScreen_ = this;
        
        setTitle(new LabelField("IMAGE " + counter_, LabelField.ELLIPSIS | LabelField.USE_ALL_WIDTH ));
        
        //Convert the byte array to a Bitmap image.
        Bitmap image = Bitmap.createBitmapFromBytes(raw, 0, -1, IMAGE_SCALING);
        
        //Two field managers to center the screen's contents.
        HorizontalFieldManager hfm1 = new HorizontalFieldManager(Field.FIELD_HCENTER);
        HorizontalFieldManager hfm2 = new HorizontalFieldManager(Field.FIELD_HCENTER);
        
        //Create the field that contains the image.
        BitmapField imageField = new BitmapField(image);
        hfm1.add(imageField);
        
        //Create the Save button that tells the system to save the image.
        ButtonField saveButton = new ButtonField("Save");
        //saveButton.setChangeListener(new SaveListener(raw));
        hfm2.add(saveButton);
        
        //Create the Cancel button that returns the user to the main camera.
        ButtonField cancelButton = new ButtonField("Cancel");
        cancelButton.setChangeListener(new CancelListener());
        hfm2.add(cancelButton);
        
        //Add the field managers to the screen.
        add(hfm1);
        add(hfm2);
    }
    
    /**
    * A listener used for the "Save" button.
    */
    private class SaveListener implements FieldChangeListener {
        /**
        * Return the raw byte array to the system.
        */
        public void fieldChanged(Field field, int context) {
            //SAVE CODE HERE. RETURN THE BYTE ARRAY TO EDDIES CODE
        }
    }
    
    /**
    * A listener used for the "Cancel" button.
    */
    private class CancelListener implements FieldChangeListener {
        /**
        * Return to the main camera screen.
        */
        public void fieldChanged(Field field, int context) {
            UiApplication.getUiApplication().popScreen(imageScreen_);
        }
    }
    
    /**
     * Handle trackball click events.
     * @see net.rim.device.api.ui.Screen#invokeAction(int)
     */   
    protected boolean invokeAction(int action) {
        boolean handled = super.invokeAction(action); 
        if(!handled) {
            switch(action) {
                case ACTION_INVOKE: // Trackball click.
                    return true;
            }
        }
        return handled;
    }
}
