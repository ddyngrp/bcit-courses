/*
 * Menu.java
 *
 * © <your company here>, 2003-2008
 * Confidential and proprietary.
 */
package src;
import net.rim.device.api.ui.Screen;
import net.rim.device.api.ui.Manager;
import net.rim.device.api.ui.container.VerticalFieldManager;
import net.rim.device.api.ui.container.FullScreen;
import net.rim.device.api.ui.container.MainScreen;
import net.rim.device.api.ui.component.LabelField;
import net.rim.device.api.ui.component.RichTextField;
import net.rim.device.api.ui.component.SeparatorField;
import net.rim.device.api.ui.component.EditField;
import net.rim.device.api.ui.component.ListField;
import net.rim.device.api.ui.component.ButtonField;
import net.rim.device.api.ui.component.ActiveAutoTextEditField;
import net.rim.device.api.ui.decor.Border;
import net.rim.device.api.ui.decor.BorderFactory;
import net.rim.device.api.ui.XYEdges;
import net.rim.device.api.ui.component.EditField;


import net.rim.device.api.ui.container.VerticalFieldManager;
import net.rim.device.api.ui.container.HorizontalFieldManager;
//import javax.microedition.lcdui.TextField;




class Menu extends MainScreen {
    public static final int LIST_SIZE   = 4;
    public static final int TEXT        = 2001;
    public static final int VIDEO       = 2002;
    public static final int AUDIO       = 2003;
    public static final int IMAGE       = 2004;
    public static final int SEND        = 2005;
    public static final int CANCEL      = 2006;
   // public static final int LI = 3;
    public static final String VIDEO_BTNLABEL = "VIDEO";
    public static final String AUDIO_BTNLABEL = "AUDIO";
    public static final String IMAGE_BTNLABEL = "IMAGE";
    public static final String SEND_BTNLABEL = "SEND";
    public static final String CANCEL_BTNLABEL = "CANCEL";
    
    private LabelField              title;
    private LabelField              imageCount;
    private LabelField              videoCount;
    private LabelField              audioCount;
    private SeparatorField          sepLine;
    private EditField               titleBar;
    private ListField               list;

  
    private ButtonField             videoButton;
    private ButtonField             textButton;
    private ButtonField             imageButton;
    private ButtonField             soundButton;
    private ButtonField             saveButton;
    private ButtonField             cancelButton;
    private HorizontalFieldManager  buttonManager;
    private HorizontalFieldManager  fileManager;
    private ActiveAutoTextEditField textField;
    MediaController mc = new MediaController();
    
    Menu()
    { 
        super();
        initialScreen();
    }
    
    void initialScreen()
    {
        title = new LabelField("Memo Logger 1.0",FIELD_HCENTER);
        this.setTitle(title);


        //create seperator
        sepLine = new SeparatorField();
        this.add(sepLine);
        
        //TITLE
        titleBar = new EditField("Title: "," ",30,EDITABLE);
        XYEdges edges = new XYEdges(2, 2, 2, 2);
        titleBar.setBorder(BorderFactory.createSimpleBorder(edges));
        this.add(titleBar);
        
        //Count Field
        videoCount = new LabelField("Total video:  "+mc.count("video"));
        imageCount = new LabelField("Total image: "+mc.count("image"));
        audioCount = new LabelField("Total audio:  "+mc.count("sound"));
        this.add(videoCount);
        this.add(imageCount);
        this.add(audioCount);
        

        
        //description box
        textField = new ActiveAutoTextEditField("Description: ", null,50,FIELD_BOTTOM);
        XYEdges border = new XYEdges(2, 2, 2, 2);
        textField.setBorder(BorderFactory.createSimpleBorder(border));
        this.add(textField);

       
       //buttons
        videoButton = new ButtonField(VIDEO_BTNLABEL);
        videoButton.setChangeListener(new ButtonListener(this.mc));

        imageButton = new ButtonField(IMAGE_BTNLABEL);
        imageButton.setChangeListener(new ButtonListener(this.mc));
        soundButton = new ButtonField(AUDIO_BTNLABEL);
        soundButton.setChangeListener(new ButtonListener(this.mc));
        saveButton = new ButtonField(SEND_BTNLABEL);
        saveButton.setChangeListener(new ButtonListener(this.mc));
        cancelButton = new ButtonField(CANCEL_BTNLABEL);
        cancelButton.setChangeListener(new ButtonListener(this.mc));
         
        buttonManager = new HorizontalFieldManager(Manager.HORIZONTAL_SCROLL | FIELD_HCENTER);
        fileManager    = new HorizontalFieldManager(Manager.HORIZONTAL_SCROLL | FIELD_HCENTER);

        buttonManager.add(videoButton);
        buttonManager.add(imageButton);
        buttonManager.add(soundButton);
        
        fileManager.add(saveButton);
        fileManager.add(cancelButton);      
        
        this.add(buttonManager);
        this.add(fileManager);
    }
} 
