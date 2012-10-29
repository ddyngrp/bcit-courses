/*
 * LoginScreen.java
 *
 * © <your company here>, 2003-2008
 * Confidential and proprietary.
 */

//http://mlogger.trollop.org:3141/MLogger/MLService.asmx

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
    
    public LoginScreen() {
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
        bf.setChangeListener(new LoginListener(edit,pass));
        ButtonField lgCancel = new ButtonField("Cancel");
        lgCancel.setChangeListener(new LoginListener(edit,pass));
        
        buttonManager.add(bf);
        buttonManager.add(lgCancel);

        add(buttonManager);
    }
} 

final class  LoginListener implements FieldChangeListener{
    private EditField nameField;
    private PasswordEditField passField;
    
    public LoginListener(EditField nameField, PasswordEditField passField){
    
      this.nameField = (EditField)nameField;
      this.passField = passField;
    }
    public void fieldChanged(Field field, int context){

        //where you pass login info to the server for checking
        ButtonField btn = (ButtonField) field;
        XMLPost xPost = new XMLPost("http://mloggerserver/");
        
        if(btn.getLabel().equals("Login")){
            //LOGIN
            String str = "";
            try {
                XML_Login_Response lr = new XML_Login_Response(
                str = xPost.postXMLData(
                    new XML_Login_Request(this.getNameField().getText(),
                            this.getPassField().getText()).toString()));
                System.err.println(str);
                if (lr.success()) {
                    //mc.sessionID(lr.sessionID());
                }
            } catch (IOException e) {
               System.err.println("epic fail");
            }
        }else if (btn.getLabel().equals("Cancel")){
            UiApplication.getUiApplication().popScreen();
        }
        
        //Status.show("username is: " + this.getNameField().getText());
       // Status.show("password is: " + this.getPassField().getText());
        
    }
    public EditField getNameField(){ return this.nameField;}
    public PasswordEditField getPassField(){return this.passField;}
}

