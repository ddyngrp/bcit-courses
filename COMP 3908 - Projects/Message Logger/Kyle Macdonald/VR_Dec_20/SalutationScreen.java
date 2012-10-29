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



class SalutationScreen extends MainScreen
{
    int value = 0;
    private String buttons[] = {"Record","Stop","Playback","Save","Cancel"};
    private VoiceNotesRecorderThread recorder;   
    private Timer timer ;
    static Date date = new Date();
    

    private GaugeField gauge;
    private ButtonField recordButton;
    private ButtonField stopButton;
    private ButtonField playButton;
    private ButtonField cancelButton;
    private ButtonField saveButton;
    
    
    public MenuItem mi = new MenuItem("Start Recording",1,1) {
        public void run() {
            recorder.run();
        }
    };
    
    public MenuItem mi1 = new MenuItem("Stop Recording",1,1) {
        public void run() {
            recorder.stop();
        }
    };
    
    public MenuItem mi2 = new MenuItem("Playback Voice",1,1) {
        public void run() {
            recorder.playback();
        }
    };
    

    public SalutationScreen()
    {   
        initializeScreen();
        recorder = new VoiceNotesRecorderThread();
        timer = new Timer();

    }
    
    void initializeScreen()
    {
        HorizontalFieldManager gaugeManager = new HorizontalFieldManager();
        HorizontalFieldManager bm = new HorizontalFieldManager(FIELD_HCENTER);
        HorizontalFieldManager bottomManager = new HorizontalFieldManager(FIELD_HCENTER);
        this.addMenuItem(mi);
        this.addMenuItem(mi1);
        this.addMenuItem(mi2);
        
        //screen items
        
        //gauge bar
       gauge = new GaugeField("", 0, 60, value, Field.FOCUSABLE);
        
        //buttons
        recordButton = new ButtonField(buttons[0],FIELD_BOTTOM);
        recordButton.setChangeListener(new AudioButtonListener());
        stopButton = new ButtonField(buttons[1]);
        stopButton.setChangeListener(new AudioButtonListener());
        playButton = new ButtonField(buttons[2]);
        playButton.setChangeListener(new AudioButtonListener());
        
        saveButton = new ButtonField(buttons[3]);
        cancelButton =new ButtonField(buttons[4]);
        
        bm.add(recordButton);
        bm.add(stopButton);
        bm.add(playButton);
        bottomManager.add(saveButton);
        bottomManager.add(cancelButton);
        
        
       // this.add(bottomManager);
        gaugeManager.add(gauge);
        
        //add to screen
        this.add(bm);
        this.add(bottomManager);
        this.add(gaugeManager);     
        
        
    }
    
    private final class AudioButtonListener implements FieldChangeListener{
        private static final String AUDIO_RECORD        = "Record";
        private static final String AUDIO_STOP          = "Stop";
        private static final String AUDIO_PLAYBACK      = "Playback";
        private static final String AUDIO_SAVE          = "Save";
        private static final String AUDIO_CANCEL        = "Cancel";
        
        private static final int _RECORD        = 30001;
        private static final int _STOP          = 30002;
        private static final int _PLAYBACK      = 30003;
        private static final int _SAVE          = 30004;
        private static final int _CANCEL        = 30005;
       
        
        public void fieldChanged(Field field, int context){
            String btnLabel;
            int button;
            //button acton handler
            ButtonField btn = (ButtonField)field;
            btnLabel = btn.getLabel();
    
            if (btnLabel.equals(AUDIO_RECORD)){
                button = _RECORD;
                //processButton(button,btn);
                }
            if (btnLabel.equals(AUDIO_STOP)){
                button = _STOP;
                //processButton(button,btn);
                }
            if (btnLabel.equals(AUDIO_PLAYBACK)){
                button = _PLAYBACK ;
                //processButton(button,btn);
                } 
            if (btnLabel.equals(Menu.CANCEL_BTNLABEL)){
                button = _CANCEL;
                //processButton(button,btn);
                }
            if (btnLabel.equals(AUDIO_SAVE )){
                button = _SAVE;
                //processButton(button,btn);
                }
            
        }
    }
}



