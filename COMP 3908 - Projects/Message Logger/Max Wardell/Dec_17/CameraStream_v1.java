import net.rim.device.api.ui.UiApplication;
import net.rim.device.api.ui.component.*;
import net.rim.device.api.ui.Field;
import net.rim.device.api.ui.container.*;
import net.rim.device.api.ui.MenuItem;
import javax.microedition.media.*;
import javax.microedition.media.control.*;
import net.rim.device.api.system.Bitmap;

/**
 * <p>CameraStream is the camera of the Trustera BlackBerry Camera.</p>
 * @author Max Wardell
 * @version 1.0
 */
public class CameraStream extends UiApplication {
                
    private MainScreen home, preview; //Various screens
    private EditField logField;          //Log used to store data and display it to the user
    ObjectChoiceField qualityField;      //
    private VideoControl vc;             //Controls the display of the video(camera, in this case)
    private String encoding;             //Defines the quality of the image
    private Player p;                    //
    private Field viewFinder;            //
    private BitmapField bitmapField;     //
    private boolean isViewfinderVisible; //
            
    //Entry point to the program
    public static void main(String[] args) {
        CameraStream app = new CameraStream();
        app.enterEventDispatcher();
    }

        private MenuItem mi = new MenuItem("Viewfinder", 1, 1) {
                public void run() {
                        try {
                                setupEncoding();
                                logField.setText("");
                                log("Active Encoding: " + encoding);
                                if(vc != null) {
                                        UiApplication.getUiApplication().invokeLater(new Runnable() {
                                                public void run() {
                                                        if(home.getFieldCount() < 3) {
                                                                home.delete(logField);
                                                                home.add(viewFinder);
                                                                home.add(logField);
                                                                viewFinder.setFocus();
                                                        }
                                                }
                                        });
                                        vc.setVisible(true);
                                        isViewfinderVisible = true;
                                        log("Initialized ViewFinder");
                                }
                                else
                                        log("VideoControl not initialized");
                        }
                        catch (Throwable e) {
                                log(e + ":" + e.getMessage());
                        }
                }
        };

    private MenuItem mi1 = new MenuItem("Take Picture", 1, 1) {
        public void run() {
                        try {
                                if(vc != null && isViewfinderVisible) {
                                        String imageType = "encoding=jpeg&width=640&height=480&quality=superfine";
                                        //Take the snapshot, store the raw bytes into an array.
                                        final byte[] imageBytes = vc.getSnapshot(encoding);
                                        UiApplication.getUiApplication().invokeLater(new Runnable() {
                                                public void run() {
                                                        if (imageBytes.length > 0 && Dialog.ask(Dialog.D_YES_NO, "Draw image?") == Dialog.YES) {
                                                                Bitmap image = Bitmap.createBitmapFromBytes(imageBytes, 0, imageBytes.length, 4);
                                                                bitmapField.setBitmap(image);
                                                                bitmapField.setSpace(5, 5);
                                                                pushScreen(preview);
                                                        }
                                                }
                                        });
                                }
                                if(isViewfinderVisible) {
                                        home.delete(viewFinder);
                                        isViewfinderVisible = false;
                                }
                        }
                        catch (Throwable e) {
                                log(e + ": " + e.getMessage());
                        }
        }
    };

        private MenuItem mi2 = new MenuItem("FullScreen", 1, 1) {
            public void run() {
                    if(vc != null) {
                            try {
                                vc.setDisplayFullScreen(true);
                                }
                                catch (MediaException e) {
                                        log(e.getMessage());
                                }
                        }
                        else
                                log("VideoControl is not initialized");
                }
        };

        private MenuItem mi3 = new MenuItem("Exit FullScreen", 1, 1) {
                public void run() {
                        if(vc != null) {
                                try {
                                        vc.setDisplayFullScreen(false);
                                }
                                catch (MediaException e) {
                                        log(e.getMessage());
                                }
                        }
                        else
                                log("VideoControl is not initialized");
                }
        };

    public CameraStream() {
        home = new MainScreen();
        logField = new EditField("Log:","");
        bitmapField = new BitmapField();
                //Add all of the menu items
                home.addMenuItem(mi);  //ViewFinder
        home.addMenuItem(mi1); //Take Picture
        home.addMenuItem(mi2); //Full Screen
        home.addMenuItem(mi3); //Exit Full Screen
        preview = new MainScreen();
        preview.add(bitmapField);

        pushScreen(home);
        try {
            /*
            Set up the Player instance to video mode.
            */
            p = Manager.createPlayer("capture://video");
            p.realize();
            p.prefetch();
            p.start();
            /*
            Initialize the VideoControl.
            */
            vc = (VideoControl) p.getControl("VideoControl");
            viewFinder = (Field)vc.initDisplayMode(VideoControl.USE_GUI_PRIMITIVE, "net.rim.device.api.ui.Field");
                }
                catch (Exception me) {
                        log(me.getMessage());
                }
                isViewfinderVisible = false;
    }
}

