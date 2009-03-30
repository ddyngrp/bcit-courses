package client;

import org.apache.xmlrpc.*;
import org.apache.xmlrpc.client.*;
import java.net.*;
import java.util.*;
import java.io.*;

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

//            // Create a request
//            Vector params = new Vector();
//            params.add("George");
                        
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            int input = -1;
            int vote;
            Vector params;

            Object[] survey = (Object[]) client.execute("survey.survey", new Vector());
            Menu(survey);

            while (true) {
                System.out.print("input > ");
                input = Integer.parseInt(br.readLine());

                if (input == 99) {
                    break;
                }
                else if (input == 0) {
                    Menu(survey);
                }
                else if (input > 0 && input < survey.length) {
                    params = new Vector(); // delete the old list
                    params.add(input);
                    vote = (Integer) client.execute("survey.vote", params);
                    System.out.println("#" + vote + " is the most popular choice.");
                }
                else if (input == survey.length) {
                    System.out.println((String) client.execute("survey.report", new Vector()));
                }
                else {
                    input = -1;
                }
            }

            
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

    public static void Menu(Object[] survey) {
        String menu = "Menu: enter 0 to reprint or 99 to exit.\n\n";

        menu += survey[0] + "\n";
        
        for (int i = 1; i < survey.length; i++) {
            menu += "\t" + i + ".  " + survey[i] + "\n";
        }

        menu += "\n\t" + survey.length + ".  Request Report\n";

        System.out.print(menu);
    }
}
