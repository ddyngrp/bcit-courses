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
        login_response(51423);
    }
    
    public static void login_request() {
        System.out.println(new XML_Login_Request("doug", "penner").toString());
    }
    
    public static void login_response(int id) {
        // WARNING!!!: do NOT EVER use "\n"!!!!
        String data = "<?xml version=\"1.0\" encoding=\"utf-8\"?>" +
            "<soap:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\">" +
                "<soap:Body>" +
                    "<UserLoginResponse xmlns=\"http://virus-box/MLogger\">" +
                        "<UserLoginResult>" + id + "</UserLoginResult>" +
                    "</UserLoginResponse>" +
                "</soap:Body>" +
            "</soap:Envelope>";
        XML_Login_Response xml = new XML_Login_Response(data);
        System.out.println("========== Status Start ==========");
        System.out.println("Success: " + xml.success());
        System.out.println("Status: " + xml.status());
        System.out.println("==========  Status End  ==========");
    }
    
    public static void post_request() {
        MediaController mc = new MediaController();
        mc.setTitle("Title");
        mc.setDescription("Description");
        mc.add(new Image("A".getBytes(), "jpg"));
        mc.add(new Image("B".getBytes(), "bmp"));
        mc.add(new Image("C".getBytes(), "png"));
        mc.add(new Video("D".getBytes(), "wmv"));
        mc.add(new Image("E".getBytes(), "mpg"));
        mc.add(new Sound("F".getBytes(), "mp3"));
        XML_Request xml = new XML_Post_Request(mc, 100);
        System.out.println(xml.toString());
    }
} 
