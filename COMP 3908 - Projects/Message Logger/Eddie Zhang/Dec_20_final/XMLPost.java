package src;

import javax.microedition.io.*;
import java.io.*;

/**
 * Posts xml documents by connecting to a server.
 */
public class XMLPost {
    private static final String path = "/MLogger/MLService.asmx";
    private static final String hostname = "mlogger.trollop.org:3141";
    
    /**
     * Connects to the specefied URL, writes to an output stream, and posts the data.
     * Then it gets the data from the URL adding it to a StringBuffer, then returns it
     * as a string.
     * 
     * @param  postData the data thats will be posted
     * @return          the string that's returned from the server
     */
    static String postXMLData(String postData) {
        HttpConnection c = null;
        InputStream is = null;
        OutputStream os = null;
        int rc;
        StringBuffer buff = new StringBuffer();

        try {
            //opens the url
            c = (HttpConnection)Connector.open("http://" + hostname + path);
            //specify the connection as a post
            c.setRequestMethod(HttpConnection.POST);
            //setting the request property
            c.setRequestProperty("Content-Type", "text/xml");
            //opening the output stream
            os = c.openDataOutputStream();

            //writing to the output stream
            os.write(postData.getBytes());
            os.flush();
            os.close();

            // Getting the response code will open the connection,
            // send the request, and read the HTTP response headers. 
            // The headers are stored until requested.
            rc = c.getResponseCode();
            System.err.println("checking connection");
            if (rc != HttpConnection.HTTP_OK) {
                System.err.println("HTTP response code: " + rc);
                throw new IOException("HTTP response code: " + rc);
            }
            
            //opens up the input stream to put the information into.
            is = c.openInputStream();

            // Get the length and process the data
            int len = (int)c.getLength();

            // stores information if length is known.
            if (len > 0) {
                int actual = 0;
                int bytesread = 0 ;
                byte[] data = new byte[len];
                
                //looping through and storing each byte into a byte array.
                while ((bytesread != len) && (actual != -1)) {
                    actual = is.read(data, bytesread, len - bytesread);
                    bytesread += actual;
                }
                
                //converting each byte into a char and appending it to a string buffer.
                for(int i=0; i < data.length; i++)
                    buff.append((char) data[i]);

            } else {
                // length is unknown.
                int ch;
                
                //converting each byte into a char, then appending to the string buffer.
                while ((ch = is.read()) != -1)
                    buff.append((char) ch);
            }
            // closing connection & streams
            if (is != null)
                is.close();
            if (c != null)
                c.close();
        } catch (ClassCastException e) {
            System.err.println("Not an HTTP URL");
        } catch (IOException e) {
            System.err.println("IOException: " + e.toString());
        }
        return buff.toString();
    }
} 

