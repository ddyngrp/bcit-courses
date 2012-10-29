/*
 * MemoMain.java
 *
 * © <your company here>, 2003-2008
 * Confidential and proprietary.
 */

import net.rim.device.api.ui.UiApplication;


/**
 * 
 */
class MemoMain extends net.rim.device.api.ui.UiApplication{
    MemoMain() 
    {
        Menu mainMenu = new Menu();  
        pushScreen(mainMenu);
    }
    public static void main(String[] args)
    {
        MemoMain memoLogger = new MemoMain();
        memoLogger.enterEventDispatcher();
        
    }
} 
