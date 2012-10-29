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
    
    public void fieldChanged(Field field, int context){
        String btnLabel;
        int button;
        //button acton handler
        ButtonField btn = (ButtonField)field;
        btnLabel = btn.getLabel();
        if (btnLabel.equals(Menu.TEXT_BTNLABEL)){
            button = Menu.TEXT;
            //call handling function
            processButton(button,btn);
            }
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
        if (btnLabel.equals(Menu.SAVE_BTNLABEL)){
            button = Menu.SAVE;
            processButton(button,btn);
            }
        
    }
    
    void processButton(int button,ButtonField btn){
        mc = new MediaController();
        switch (button){
            case Menu.TEXT:
                //Status.show("Button pressed: " + btn.getLabel());
                LoginScreen ls = new LoginScreen();
                UiApplication.getUiApplication().pushScreen(ls);
                
                break;
            case Menu.SAVE:
                Status.show("Button pressed: " + btn.getLabel());
                break;
            case Menu.VIDEO:
                //Status.show("Button pressed: " + btn.getLabel());
              /*  try{
                        if(mc.add(new Video())==false)
                            throw new CancelException();
                        
                }catch (CancelException e){
                    Status.show(e.toString());
                }finally{
                   ;//regenerate item_list
                   break;
                }*/
                break;
            case Menu.AUDIO:
                //Status.show("Button pressed: " + btn.getLabel());
                SalutationScreen ss = new SalutationScreen();
                UiApplication.getUiApplication().pushScreen(ss);
              //  UiApplication.getUiApplication().pushGlobalScreen(ss);
                break;
            case Menu.CANCEL:
                Status.show("Button pressed: " + btn.getLabel());
                break;
            case Menu.IMAGE:
                try{
                    CameraStream cs = new CameraStream(mc);
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

