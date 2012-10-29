/*
 * XML_Post_Response.java
 *
 * MLogger, 2008
 * Confidential and proprietary.
 */
package src; 
import java.io.IOException;
import javax.microedition.xml.rpc.*     ;
import java.io.InputStream;
import java.io.ByteArrayInputStream;
import net.rim.device.api.xml.parsers.DocumentBuilderFactory;
import org.w3c.dom.Element;
import net.rim.device.api.xml.parsers.ParserConfigurationException;
import org.xml.sax.SAXException;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import net.rim.device.api.crypto.CryptoException;

public class XML_Post_Response implements XML_Response {
    
    /**
    * Status of Memo posting.
    */
    protected int status;
    
    /**
     * Constructor
     * @param data XML to be parsed to grab a memo post status.
     */
    XML_Post_Response(String data) {
        this.status = XML_Post_Response.PARSING_ERROR;
        try {
            // get root
            Element root = DocumentBuilderFactory.newInstance().newDocumentBuilder().parse(new ByteArrayInputStream(data.getBytes())).getDocumentElement();
            root.normalize();
            // turn root into node
            Node node = root;
            // get status value
            this.status = Integer.parseInt(node.getFirstChild().getFirstChild().getFirstChild().getFirstChild().getNodeValue());
            // Exception Handline
        } catch (ParserConfigurationException e) {
            System.err.println("Caught ParserConfigurationException: " + e.toString());
        } catch (SAXException e) {
            System.err.println("Caught SAXException: " + e.toString());
        } catch (IOException e) {
            System.err.println("Caught IOException: " + e.toString());
        }
    }
    
    /**
     * Success of memo being posted.
     * @return The success of the memo posting.
     */
    public boolean success() {
        return this.status == 1;
    }
    
    /**
     * status of memo being posted.
     * @return The status of the memo posting. (see XML_Response for error codes)
     */
    public int status() {
        return this.status;
    }
}
