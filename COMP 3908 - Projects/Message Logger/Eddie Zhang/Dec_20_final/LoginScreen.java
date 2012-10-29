/*
 * LoginScreen.java
 *
 * © <your company here>, 2003-2008
 * Confidential and proprietary.
 */

package src;
import net.rim.device.api.ui.container.FullScreen;
import net.rim.device.api.ui.component.EditField;
import net.rim.device.api.ui.component.PasswordEditField;
import net.rim.device.api.ui.component.ButtonField;
import net.rim.device.api.ui.component.LabelField;
import net.rim.device.api.ui.Field;
import net.rim.device.api.ui.decor.BorderFactory;
import net.rim.device.api.ui.XYEdges;
import net.rim.device.api.ui.FieldChangeListener;
import net.rim.device.api.ui.container.HorizontalFieldManager;
import net.rim.device.api.ui.Manager;
import net.rim.device.api.ui.Screen;
import net.rim.device.api.ui.component.Status;
import net.rim.device.api.ui.container.MainScreen;
import net.rim.device.api.ui.UiApplication;
import java.io.IOException;

class LoginScreen extends MainScreen {
    private HorizontalFieldManager buttonManager;
    
    public LoginScreen(MediaController mc) {
        
        buttonManager = new HorizontalFieldManager(Manager.HORIZONTAL_SCROLL | FIELD_HCENTER);
               
        LabelField lf = new LabelField("Login Screen", FIELD_HCENTER);
        XYEdges edges = new XYEdges(1, 1, 1, 1);
        lf.setBorder(BorderFactory.createSimpleBorder(edges));
        add(lf);
        
        EditField edit = new EditField("Username: ", "",30,EDITABLE );
        add(edit);
        PasswordEditField pass = new PasswordEditField("Password: ", "",30,EDITABLE);
        add(pass);
        
        ButtonField bf = new ButtonField("Login");
        bf.setChangeListener(new LoginListener(mc, edit,pass));
        ButtonField lgCancel = new ButtonField("Cancel");
        lgCancel.setChangeListener(new LoginListener(mc, edit,pass));
        
        buttonManager.add(bf);
        buttonManager.add(lgCancel);

        add(buttonManager);
    }
} 

final class  LoginListener implements FieldChangeListener{
    private EditField nameField;
    private PasswordEditField passField;
    private MediaController mc;
    
    public LoginListener(MediaController mc, EditField nameField, PasswordEditField passField){
        this.mc = mc;
      this.nameField = nameField;
      this.passField = passField;
    }
    public void fieldChanged(Field field, int context){

        //where you pass login info to the server for checking
        ButtonField btn = (ButtonField) field;
        
        //LOGIN
        if(btn.getLabel().equals("Login")){
            XML_Login_Request  request  = new XML_Login_Request(this.nameField.getText(), this.passField.getText());
            XML_Login_Response response = new XML_Login_Response(XMLPost.postXMLData(request.toString()));
            System.out.println("SessionID: " + response.sessionID());
            mc.sessionID(response.sessionID());
            if (response.success()) {
                UiApplication.getUiApplication().popScreen();
            }
        } else if (btn.getLabel().equals("Cancel")) {
            UiApplication.getUiApplication().popScreen();
        }
    }
}

