package src;
import javax.microedition.media.*;
import javax.microedition.media.Manager;
import javax.microedition.media.control.*;
import java.io.*;
import net.rim.device.api.ui.component.*;
import net.rim.device.api.ui.*;
import net.rim.device.api.system.Application;

/**
 * The thread that will be used to start/stop recording, and play back audio.
 */
final class VoiceNotesRecorderThread extends Thread
{
    /**
     * Used for recording, and playing music
     */
    private Player _player;
    
    /**
     * Allows the player to start recording
     */
    private RecordControl _rcontrol;
    
    /**
     * The byte stream to save the recorded audio to
     */
    private ByteArrayOutputStream _output;
    
    /**
     * The final format of this class that the audio is saved as
     */
    private byte _data[];
    
    /**
     * Used to initialize an instance of this object
     */
    VoiceNotesRecorderThread() {}
    
    /**
     * The get method of the size of the output stream
     * @return the size of the output stream
     */
    public int getSize() {
        return (_output != null ? _output.size() : 0);
    }
    
    /**
     * The get method of the recorded audio
     * @return the recorded audio as a byte array
     */
    public byte[] getVoiceNote() {
        return _data;
    }
    
    /**
     * Starts to the player object in record mode.
     */
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
            // waiting till the button has been selected.
            UiApplication.getUiApplication().invokeAndWait(new Runnable() {
                public void run() {
                    Dialog.inform(e.toString());
                }
            });
        }  
    }
    
    /**
     * Stop recording, record data from the OutputStream,
     * close the OutputStream and player.
     */
    public void stop() {
        try {
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
    
    /**
     * Plays back the recorded audio (the byte array that was saved in the stop
     * method, and is called in getVoiceNote() method.
     */
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

