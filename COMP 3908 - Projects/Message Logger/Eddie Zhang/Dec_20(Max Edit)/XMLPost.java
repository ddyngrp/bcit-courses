package src;

import javax.microedition.io.*;
import java.io.*;
//http://mlogger.trollop.org:3141/MLogger/MLService.asmx



/**
 * Posts xml documents by connecting to a server.
 */
public class XMLPost {
    String url;
    
    /**
     * Specifies the server to post the xml to.
     * @param site the URL of the server
     */
    public XMLPost(String site) {
        url = site;
    }
    
    /**
     * Connects to the specefied URL, writes to an output stream, and posts the data.
     * Then it gets the data from the URL adding it to a StringBuffer, then returns it
     * as a string.
     * 
     * @param  postData the data thats will be posted
     * @return          the string that's returned from the server
     */
    String postXMLData(String postData) throws IOException {
        HttpConnection c = null;
        InputStream is = null;
        OutputStream os = null;
        int rc;
        StringBuffer buff = new StringBuffer();

        try {
            //opens the url
            c = (HttpConnection)Connector.open(url);
            //specify the connection as a post
            c.setRequestMethod(HttpConnection.POST);
            //setting the request property
            c.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");
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
        } catch (ClassCastException e) {
            throw new IllegalArgumentException("Not an HTTP URL");
        } finally {
            // closing connection & streams
            if (is != null)
                is.close();
            if (c != null)
                c.close();
        }
        return buff.toString();
    }
} 

