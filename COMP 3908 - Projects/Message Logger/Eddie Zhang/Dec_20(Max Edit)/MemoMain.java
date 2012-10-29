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
        
        /* Login In */
 /*       XML_Login_Response lr = new XML_Login_Response(
            postXMLData(
                new XML_Login_Request("uName", "passWord").toString()
            )
        );
        if (lr.success()) {
            mc.sessionID(lr.sessionID());
        }*/
        /* End
        
        /* Posting */
        
      /*  XML_Post_Response pr = new XML_Login_Response(
            postXMLData(
                new XML_Post_Request(mc).toString()
            )
        );*/
       /* if (pr.success()) {
            // Successful
        } else {
            switch (pr.status()) {
                case XML_Response.INVALID_AUTHORIZATION:
                    login();
                    break;
                case XML_Response.PARSING_ERROR:
                    //
                    break;
                case XML_Response.SERVER_ERROR:
                    //
                    break;
            }
        }
        */
        /* End */
        
        
        
        
        pushScreen(mainMenu);
       // pushScreen(ls);
    }
    public static void main(String[] args)
    {
        MemoMain memoLogger = new MemoMain();
        memoLogger.enterEventDispatcher();
        
    }
} 
