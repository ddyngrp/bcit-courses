/*
 * ButtonListenner.java
 *
 * © <your company here>, 2003-2008
 * Confidential and proprietary.
 */

package src;
import java.lang.Exception;
import net.rim.device.api.ui.FieldChangeListener;
import net.rim.device.api.ui.Field;
import net.rim.device.api.ui.component.ButtonField;
import net.rim.device.api.ui.component.Status;
import net.rim.device.api.ui.UiApplication;


/**
 * 
 */
public final class ButtonListener implements FieldChangeListener {
    private MediaController mc;
    
    ButtonListener(MediaController mc) {
        this.mc = mc;
    }
    
    public void fieldChanged(Field field, int context){
        String btnLabel;
        int button;
        //button acton handler
        ButtonField btn = (ButtonField)field;
        btnLabel = btn.getLabel();

        if (btnLabel.equals(Menu.IMAGE_BTNLABEL)){
            button = Menu.IMAGE;
            processButton(button,btn);
            }
        if (btnLabel.equals(Menu.AUDIO_BTNLABEL)){
            button = Menu.AUDIO;
            processButton(button,btn);
            }
        if (btnLabel.equals(Menu.VIDEO_BTNLABEL)){
            button = Menu.VIDEO;
            processButton(button,btn);
            } 
        if (btnLabel.equals(Menu.CANCEL_BTNLABEL)){
            button = Menu.CANCEL;
            processButton(button,btn);
            }
        if (btnLabel.equals(Menu.SEND_BTNLABEL)){
            button = Menu.SEND;
            processButton(button,btn);
            }
        
    }
    
    void processButton(int button,ButtonField btn){
        switch (button){

            case Menu.SEND:
                if (this.mc.loggedIn()) {
                    // Post Memo
                    mc.fake();
                    XML_Post_Request request = new XML_Post_Request(this.mc);
                    XML_Post_Response response = new XML_Post_Response(XMLPost.postXMLData(request.toString()));
                    System.out.println("Status: " + response.status());
                } else {
                    // Log In
                    LoginScreen loginScreen = new LoginScreen(this.mc);
                    UiApplication.getUiApplication().pushScreen(loginScreen);
                }
                break;
            case Menu.VIDEO:
                Status.show("Video Field will be implemented.");
                break;
            case Menu.AUDIO:
                //Status.show("Button pressed: " + btn.getLabel());
                AudioScreen ss = new AudioScreen(this.mc);
                UiApplication.getUiApplication().pushScreen(ss);
                break;
            case Menu.CANCEL:
                Status.show("Button pressed: " + btn.getLabel());
                break;
            case Menu.IMAGE:
                try{
                    CameraStream cs = new CameraStream(this.mc);
                    UiApplication.getUiApplication().pushScreen(cs);
                        
                }catch (CancelException e){
                    Status.show(e.toString());
                }finally{
                    
                   ;//regenerate item_list
                   break;
                }

            default:
                break;
   
        }
    }
} 

