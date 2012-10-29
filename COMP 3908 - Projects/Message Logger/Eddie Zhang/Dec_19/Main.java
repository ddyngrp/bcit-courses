/*
 * Main.java
 *
 * MLogger, 2008
 * Confidential and proprietary.
 */

import net.rim.device.api.crypto.*;
import java.io.IOException;

public class Main {
    public static void main(String args[]) {
        post_request();
    }
    
    public static void login_request() {
        System.out.println(new XML_Login_Request("doug", "penner").toString());
    }
    
    public static void login_response(boolean valid) {
        String data = "";
        if (valid) {
            data = "<!-- Response for user login -->\n" +
            "<?xml version=\"1.0\"?>\n" +
            "<soap:Envelope xmlns:soap=\"http://www.w3.org/2001/12/soap-envelope\" soap:encodingStyle=\"http://www.w3.org/2001/12/soap-encoding\">\n" +
            "   <soap:Body xmlns:mL=\"http://www.example.org/MLogger\">\n" +
            "       <m:UserLoginResponse>\n" +
            "           <m:SessionID>Some large random number</m:SessionID>\n" +
            "       </m:UserLoginResponse>\n" +
            "   </soap:Body>\n" +
            "</soap:Envelope>";
        } else {
            data = "<!-- Response for user login -->\n" +
            "<?xml version=\"1.0\"?>\n" +
            "<soap:Envelope xmlns:soap=\"http://www.w3.org/2001/12/soap-envelope\" soap:encodingStyle=\"http://www.w3.org/2001/12/soap-encoding\">\n" +
            "   <soap:Body xmlns:mL=\"http://www.example.org/MLogger\">\n" +
            "       <m:UserLoginResponse>\n" +
            "           <m:LoginError>Invalid User Name or Password.</m:LoginError>\n" +
            "       </m:UserLoginResponse>\n" +
            "   </soap:Body>\n" +
            "</soap:Envelope>";
        }
        XML_Login_Response xml = new XML_Login_Response(data);
        System.out.println("========== Status ==========");
        System.out.println("Success: " + xml.success());
        System.out.println("Status: " + xml.status());
    }
    
    public static void post_request() {
        MediaController mc = new MediaController();
        mc.setTitle("Title");
        mc.setDescription("Description");
        mc.add(new Image());
        mc.add(new Image());
        mc.add(new Image());
        mc.add(new Video());
        mc.add(new Video());
        mc.add(new Sound());
        XML_Request xml = new XML_Post_Request(mc, 100);
        System.out.println(xml.toString());
    }
} 
