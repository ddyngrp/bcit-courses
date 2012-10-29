/*
 * Menu.java
 *
 * © <your company here>, 2003-2008
 * Confidential and proprietary.
 */
import net.rim.device.api.ui.Screen;
import net.rim.device.api.ui.container.FullScreen;
import net.rim.device.api.ui.container.MainScreen;
import net.rim.device.api.ui.component.LabelField;
import net.rim.device.api.ui.component.RichTextField;
import net.rim.device.api.ui.component.SeparatorField;
import net.rim.device.api.ui.component.EditField;
import net.rim.device.api.ui.component.ListField;
import net.rim.device.api.ui.decor.Border;
import net.rim.device.api.ui.decor.BorderFactory;
import net.rim.device.api.ui.XYEdges;


/**
 * 
 */
 
 

class Menu extends MainScreen {
    public static final int LIST_SIZE = 6;
    private LabelField title;
    private SeparatorField sepLine;
    private EditField titleBar;
    private ListField list;
    
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
        titleBar = new EditField("Titile: "," ",30,EDITABLE);
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
        
        
        
    }
    
} 
