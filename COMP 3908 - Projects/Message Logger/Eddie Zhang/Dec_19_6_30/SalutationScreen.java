package src;
import net.rim.device.api.ui.UiApplication;
import net.rim.device.api.ui.component.*;
import net.rim.device.api.ui.Field;
import net.rim.device.api.ui.container.*;
import net.rim.device.api.ui.MenuItem;
import javax.microedition.media.*;
import javax.microedition.media.control.*;
import net.rim.device.api.ui.component.*;
import net.rim.device.api.ui.container.HorizontalFieldManager;
import net.rim.device.api.ui.container.VerticalFieldManager;
import net.rim.device.api.ui.component.BitmapField;
import java.util.*;


/**
 * Will Generate a screen that will allow for recording, and playing back audio
 * sounds.
 */
class SalutationScreen extends MainScreen
{
    int value = 0;
    String buttons[] = {"Record","Stop","Playback","Cancel"};
    
    /**
     * The thread that will take care of recording audio
     */
    private VoiceNotesRecorderThread recorder;
    
    /**
     * The timer that the recording is in sync with
     */
    private Timer timer ;

    /**
     * Used to fill up over a certain amount of time and automatically stop recording when filled up
     */
    private GaugeField gauge;
    
    /**
     * The button that will start recording
     */
    private ButtonField recordButton;
    
    /**
     * The button that will stop recording
     */
    private ButtonField stopButton;
    
    /**
     * The button that will play back the recorded audio
     */
    private ButtonField playButton;
    
    /**
     * The button that will cancel whatever is happening, and go back to the main screen
     */
    private ButtonField cancelButton;

    /**
     * Generates an instance of a screen with a timer and a recorder
     */
    public SalutationScreen() {   
        initializeScreen();
        recorder = new VoiceNotesRecorderThread();
        timer = new Timer();
    }

    /**
     * Generates a menu item on the thumbwheel track that will start recording
     */
    public MenuItem mi = new MenuItem("Start Recording",1,1) {
        public void run() {
            recorder.run();
        }
    };
    
    /**
     * Generates a menu item on the thumbwheel track that will stop recording
     */
    public MenuItem mi1 = new MenuItem("Stop Recording",1,1) {
        public void run() {
            recorder.stop();
        }
    };
    
    /**
     * Generates a menu item on the thumbwheel track that will play back the recorded voice
     */
    public MenuItem mi2 = new MenuItem("Playback Voice",1,1) {
        public void run() {
            recorder.playback();
        }
    };
    
    /**
     * Displays everything that needs to be on the screen.
     */
    void initializeScreen() {
        
        //creates the managers for each type of ui object.
        HorizontalFieldManager gaugeManager = new HorizontalFieldManager();
        HorizontalFieldManager buttonManager = new HorizontalFieldManager(FIELD_HCENTER);
        VerticalFieldManager bottomManager = new VerticalFieldManager(FIELD_HCENTER);
        
        //adds the menu items onto the trackwheel
        this.addMenuItem(mi);
        this.addMenuItem(mi1);
        this.addMenuItem(mi2);
        
        //screen items
        //gauge bar that is slowly filled up, till it reaches a certain time
        gauge = new GaugeField("", 0, 60, value, Field.FOCUSABLE);
        
        //buttons
        recordButton = new ButtonField(buttons[0],FIELD_BOTTOM);
        stopButton = new ButtonField(buttons[1]);
        playButton = new ButtonField(buttons[2]);
        cancelButton =new ButtonField(buttons[3]);
        
        //adds all the buttons to their respective managers.
        buttonManager.add(recordButton);
        buttonManager.add(stopButton);
        buttonManager.add(playButton);
        buttonManager.add(cancelButton);
        bottomManager.add(buttonManager);
        gaugeManager.add(gauge);
        
        //adds the managers to the screen
        this.add(bottomManager);
        this.add(gaugeManager); 
    }
}



