import net.rim.device.api.ui.UiApplication;
import net.rim.device.api.ui.component.*;
import net.rim.device.api.ui.Field;
import net.rim.device.api.ui.container.*;
import net.rim.device.api.ui.MenuItem;
import javax.microedition.media.*;
import javax.microedition.media.control.*;
import net.rim.device.api.ui.component.*;
import java.util.*;

class SalutationScreen extends UiApplication
{
    int value = 0;
    VoiceNotesRecorderThread recorder = new VoiceNotesRecorderThread();
    GaugeField gauge = new GaugeField("", 0, 60, value, Field.FOCUSABLE);
    Timer timer = new Timer();
    static Date date = new Date();
    
    private MainScreen home;
    
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
    
    public static void main(String args[]) {
        date.setTime(1000);
        SalutationScreen ss = new SalutationScreen();
        ss.enterEventDispatcher();
    }
    
    public SalutationScreen()
    {   
        home = new MainScreen();
        home.addMenuItem(mi);
        home.addMenuItem(mi1);
        home.addMenuItem(mi2);
        pushScreen(home);
    }
}



