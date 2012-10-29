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
    private SeparatorField          sepLine;
    private EditField               titleBar;
    private ListField               list;
    //private VerticalFieldManager    titleManager;
    //private VerticalFieldManager
  //  private VerticalFieldManager listManager;
  
    private ButtonField             videoButton;
    private ButtonField             textButton;
    private ButtonField             imageButton;
    private ButtonField             soundButton;
    private ButtonField             saveButton;
    private ButtonField             cancelButton;
    private HorizontalFieldManager  buttonManager;
    private HorizontalFieldManager  fileManager;
    private ActiveAutoTextEditField textField;
    
    Menu()
    { 
        super();
        initialScreen();
    }
    
    void initialScreen()
    {
        title = new LabelField("Memo Logger 1.0",FIELD_HCENTER);
        this.setTitle(title);
       // titleManager = new VerticalFieldManager(Manager.VERTICAL_SCROLL|FIELD_RIGHT);
      //  LabelField subtitle = new LabelField("right",FIELD_HCENTER);
      //  titleManager.add(subtitle);

        //create seperator
        sepLine = new SeparatorField();
        this.add(sepLine);
        
        //TITLE
        titleBar = new EditField("Title: "," ",30,EDITABLE);
        XYEdges edges = new XYEdges(1, 1, 1, 1);
        titleBar.setBorder(BorderFactory.createSimpleBorder(edges));
        this.add(titleBar);
        
        //CHOICE LIST
        String[] listItems = new String[]{"Text","Video","Audio"};
        list = new ListField();
        list.setSize(LIST_SIZE);
        list.setCallback(new ListBoxCallBack());
                                                                                                                                                                                                                                  
        this.add(list);
        
        //description box
        textField = new ActiveAutoTextEditField("Description: ", null,50,FIELD_BOTTOM);
        this.add(textField);

       
       //buttons
        videoButton = new ButtonField(VIDEO_BTNLABEL);
        videoButton.setChangeListener(new ButtonListener());

        imageButton = new ButtonField(IMAGE_BTNLABEL);
        imageButton.setChangeListener(new ButtonListener());
        soundButton = new ButtonField(AUDIO_BTNLABEL);
        soundButton.setChangeListener(new ButtonListener());
        saveButton = new ButtonField(SEND_BTNLABEL);
        saveButton.setChangeListener(new ButtonListener());
        cancelButton = new ButtonField(CANCEL_BTNLABEL);
        cancelButton.setChangeListener(new ButtonListener());
         
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
