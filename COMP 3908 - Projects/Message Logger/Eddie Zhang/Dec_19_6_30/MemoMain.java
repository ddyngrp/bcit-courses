/*
 * MemoMain.java
 *
 * © <your company here>, 2003-2008
 * Confidential and proprietary.
 */
 package src;

import net.rim.device.api.ui.UiApplication;


/**
 * 
 */
class MemoMain extends UiApplication{
    MemoMain() 
    {
        Menu mainMenu = new Menu();
        //LoginScreen ls = new LoginScreen();  
        pushScreen(mainMenu);
       // pushScreen(ls);
    }
    public static void main(String[] args)
    {
        MemoMain memoLogger = new MemoMain();
        memoLogger.enterEventDispatcher();
        
    }
} 
