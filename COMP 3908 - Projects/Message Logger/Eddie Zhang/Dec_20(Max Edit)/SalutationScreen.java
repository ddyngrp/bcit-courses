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
import net.rim.device.api.ui.FieldChangeListener;

/**
 * Will Generate a screen that will allow for recording, and playing back audio
 * sounds.
 */
class SalutationScreen extends MainScreen
{
    /**
     * The value of the gauge field
     */
    int value = 0;

    /**
     * The labels of each button
     */
    private String buttons[] = {"Record","Stop","Playback","Cancel"};

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
     * A MediaController used to grab the saved image.
     */
    private MediaController mc_;
    
    /**
     * Generates an instance of a screen with a timer and a recorder
     */
    public SalutationScreen(MediaController mc) {
        this.mc_ = mc;
           
        initializeScreen();
        recorder = new VoiceNotesRecorderThread(mc_);
        timer = new Timer();
    }
    
    /**
     * Displays everything that needs to be on the screen.
     */
    void initializeScreen()
    {
	//creates the managers for each type of ui object.
        HorizontalFieldManager gaugeManager = new HorizontalFieldManager();
        HorizontalFieldManager buttonManager = new HorizontalFieldManager(FIELD_HCENTER);
        VerticalFieldManager bottomManager = new VerticalFieldManager(FIELD_HCENTER);

        //screen items
	    
        //gauge bar
        gauge = new GaugeField("", 0, 60, value, Field.FOCUSABLE);
        
        //buttons
        recordButton = new ButtonField(buttons[0],FIELD_BOTTOM);
        recordButton.setChangeListener(new AudioButtonListener());
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
        
        //add to screen
           
        this.add(bottomManager);
        this.add(gaugeManager);     
        
        
    }
    
    /**
     * Listens for when each button is being pressed on the screen
     */
    private final class AudioButtonListener implements FieldChangeListener{
        
        /**
         * Label for record button
         */
	private static final String AUDIO_RECORD        = "Record";
	    
        /**
         * Label for stop recording button
         */
        private static final String AUDIO_STOP          = "Stop";
	    
        /**
         * Label for playing back the audio
         */
        private static final String AUDIO_PLAYBACK      = "Playback";
	    
        /**
         * Label for exiting the audio screen
         */
        private static final String AUDIO_CANCEL        = "Cancel";
        
        /**
         * Macros for holding an integer value for each button
         */
        private static final int _RECORD        = 30001;
        private static final int _STOP          = 30002;
        private static final int _PLAYBACK      = 30003;
        private static final int _CANCEL        = 30004;
        
        
        public void fieldChanged(Field field, int context){
            String btnLabel;
            int button;
            //button acton handler
            ButtonField btn = (ButtonField)field;
            btnLabel = btn.getLabel();
    
            if (btnLabel.equals(AUDIO_RECORD)){
                button = _RECORD;
                recorder.run();
                }
            if (btnLabel.equals(Menu.AUDIO_BTNLABEL)){
                button = _STOP;
                recorder.stop();
                }
            if (btnLabel.equals(Menu.VIDEO_BTNLABEL)){
                button = _PLAYBACK ;
                recorder.playback();
                } 
            if (btnLabel.equals(Menu.CANCEL_BTNLABEL)){
                button = _CANCEL;
                
                }
            if (btnLabel.equals(Menu.SEND_BTNLABEL)){
                button = Menu.SEND;
                //processButton(button,btn);
                }
            
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



