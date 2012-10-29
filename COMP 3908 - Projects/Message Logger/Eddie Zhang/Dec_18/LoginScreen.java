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

        add(bf);
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
        Status.show("username is: " + this.getNameField().getText());
        Status.show("password is: " + this.getPassField().getText());
        
    }
    public EditField getNameField(){ return this.nameField;}
    public PasswordEditField getPassField(){return this.passField;}
}

