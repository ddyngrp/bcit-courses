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
import net.rim.device.api.ui.component.BitmapField;
import java.util.*;



class SalutationScreen extends MainScreen
{
    int value = 0;
    String buttons[] = {"Record","Stop","Playback","Cancel"};
    private VoiceNotesRecorderThread recorder;   
    private Timer timer ;
    static Date date = new Date();
    

    private GaugeField gauge;
    private ButtonField recordButton;
    private ButtonField stopButton;
    private ButtonField playButton;
    private ButtonField cancelButton;
    /*
    
    Eddie's to do.... 
    
    - turn these 3 'menu items' into buttons instead.
    - get this class to extend MainScreen instead
    - put main's code into a constructor
    - get it to compile...
    - stop acting so ghey.
    
    */
    
    
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
    
  /*  public static void main(String args[]) {
        date.setTime(1000);
        SalutationScreen ss = new SalutationScreen();
        ss.enterEventDispatcher();
    }
    */
    public SalutationScreen()
    {   
        initializeScreen();
        recorder = new VoiceNotesRecorderThread();
        timer = new Timer();

    }
    
    void initializeScreen()
    {
        HorizontalFieldManager gaugeManager = new HorizontalFieldManager();
        HorizontalFieldManager buttonManager = new HorizontalFieldManager();
        this.addMenuItem(mi);
        this.addMenuItem(mi1);
        this.addMenuItem(mi2);
        
        //screen items
        
        //gauge bar
        gauge = new GaugeField("", 0, 60, value, Field.FOCUSABLE);
        gaugeManager.add(gauge);
        
        //buttons
        recordButton = new ButtonField(buttons[0]);
        stopButton = new ButtonField(buttons[1]);
        playButton = new ButtonField(buttons[2]);
        cancelButton =new ButtonField(buttons[3]);;
        
        
        
        
        
        
    }
}



