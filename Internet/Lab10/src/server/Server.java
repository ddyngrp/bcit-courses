package server;

import org.apache.xmlrpc.webserver.*;
import org.apache.xmlrpc.*;
import org.apache.xmlrpc.server.*;

/**
 *
 * @author Steffen L. Norgren
 */
public class Server implements SurveyServer {

    public String[] survey() {
        String[] tmp = {"1", "2", "3"};
        return tmp;
    }

    public int vote(int item) {
        return item;
    }

    public String report() {
        String tmp = "asdasd";
        return tmp;
    }

    public final static int PORT = 2000;

    public static void main(String[] args) {
        try {
            // Initialize the server
            System.out.println("Starting XML-RPC server ...");
            WebServer server = new WebServer(PORT);
            XmlRpcServer xmlRpcServer = server.getXmlRpcServer();

            // Register the handler class
            PropertyHandlerMapping phm = new PropertyHandlerMapping();
            phm.addHandler("survey", SurveyServer.class);
            xmlRpcServer.setHandlerMapping(phm);
            System.out.println("Registered SurveyHandler class to [survey]");

            // Tweak the configuration
            XmlRpcServerConfigImpl serverConfig =
                    (XmlRpcServerConfigImpl) xmlRpcServer.getConfig();
            serverConfig.setEnabledForExtensions(true);
            serverConfig.setContentLengthOptional(false);

            // Start the server
            server.start();
            System.out.println("Now accepting requests...");
        }
        catch (XmlRpcException xe) {
            System.out.println("Arghh ... " + xe.getMessage());
        }
        catch (java.io.IOException ioe) {
            System.out.println("Could not start server: " + ioe.getMessage());
        }
    }
}
