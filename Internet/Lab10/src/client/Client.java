package client;

import org.apache.xmlrpc.*;
import org.apache.xmlrpc.client.*;
import java.net.*;
import java.util.*;

/**
 *
 * @author Steffen L. Norgren
 */
public class Client {

    public final static int PORT = 2000;

    public static void main(String[] args) {
        try {
            // Specify the server
            XmlRpcClientConfigImpl config = new XmlRpcClientConfigImpl();
            config.setServerURL(new URL("http://localhost:" + PORT));
            // Setup the client
            XmlRpcClient client = new XmlRpcClient();
            client.setConfig(config);

            // Create a request
            Vector params = new Vector();
            params.add("George");
            // Make a request and print the result
            String result = (String) client.execute("survey.report", new Vector());
            System.out.println(result);

        }
        catch (java.net.MalformedURLException ex) {
            System.out.println("Incorrect URL for XML-RPC server format: " + ex.getMessage());
        }
        catch (XmlRpcException ex) {
            System.out.println("XML-RPC Exception: " + ex.getMessage());
        }
        catch (java.io.IOException ex) {
            System.out.println("IO Exception: " + ex.getMessage());
        }
    }
}
