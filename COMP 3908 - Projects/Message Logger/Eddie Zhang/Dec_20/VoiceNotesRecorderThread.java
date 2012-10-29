package src;
import javax.microedition.media.*;
import javax.microedition.media.Manager;
import javax.microedition.media.control.*;
import java.io.*;
import net.rim.device.api.ui.component.*;
import net.rim.device.api.ui.*;
import net.rim.device.api.system.Application;

final class VoiceNotesRecorderThread extends Thread
{
    private Player _player;
    private RecordControl _rcontrol;
    private ByteArrayOutputStream _output;
    private byte _data[];
    
    VoiceNotesRecorderThread() {}
    
    public int getSize() {
        return (_output != null ? _output.size() : 0);
    }
    public byte[] getVoiceNote() {
        return _data;
    }
    public void run() {
        try {
            // Create a Player that records live audio.
            _player = Manager.createPlayer("capture://audio");
            _player.realize();
            // Get the RecordControl, configure the record stream,
            _rcontrol = (RecordControl)_player.getControl("RecordControl");
            //Create a ByteArrayOutputStream to record the audio stream.
            _output = new ByteArrayOutputStream();
            _rcontrol.setRecordStream(_output);
            _rcontrol.startRecord();
            _player.start();
            
        } catch (final Exception e) {
            UiApplication.getUiApplication().invokeAndWait(new Runnable() {
                public void run() {
                    Dialog.inform(e.toString());
                }
            });
        }  
    }
    public void stop() {
        try {
            // Stop recording, record data from the OutputStream,
            // close the OutputStream and player.
            _rcontrol.commit();
            _data = _output.toByteArray();
            _output.close();
            _player.close();
        } catch (Exception e) {
            synchronized (UiApplication.getEventLock()) {
                Dialog.inform(e.toString());
            }
        }
    }
    
    public void playback() {
        try {
        InputStream input = new ByteArrayInputStream(_data);
        _player = Manager.createPlayer(input, "audio/X-wav");
        _player.start();
        } catch (final Exception e) {
            UiApplication.getUiApplication().invokeAndWait(new Runnable() {
                public void run() {
                    Dialog.inform(e.toString());
                }
            });
        }
    }
}

