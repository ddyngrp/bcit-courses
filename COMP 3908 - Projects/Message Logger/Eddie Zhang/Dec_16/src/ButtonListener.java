/*
 * ButtonListenner.java
 *
 * © <your company here>, 2003-2008
 * Confidential and proprietary.
 */

package src;
import net.rim.device.api.ui.FieldChangeListener;
import net.rim.device.api.ui.Field;
import net.rim.device.api.ui.component.ButtonField;
import net.rim.device.api.ui.component.Status;




/**
 * 
 */
public final class ButtonListener implements FieldChangeListener {
   
    
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
        switch (button){
            case Menu.TEXT:
                Status.show("Button pressed: " + btn.getLabel());
                break;
            case Menu.SAVE:
                Status.show("Button pressed: " + btn.getLabel());
                break;
            case Menu.VIDEO:
                Status.show("Button pressed: " + btn.getLabel());
                break;
            case Menu.AUDIO:
                Status.show("Button pressed: " + btn.getLabel());
                break;
            case Menu.CANCEL:
                Status.show("Button pressed: " + btn.getLabel());
                break;
            case Menu.IMAGE:
                Status.show("Button pressed: " + btn.getLabel());
                break;
            default:
                break;
   
        }
    }
    
    
} 




