/*
 * XML_Login_Response.java
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


/*
    <?xml version="1.0" encoding="utf-8"?>
    <soap:Envelope xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">
    <soap:Body>
        <UserLoginResponse xmlns="http://virus-box/MLogger">
            <UserLoginResult>long</UserLoginResult>
        </UserLoginResponse>
    </soap:Body>
    </soap:Envelope>
*/

/**
 * XML Login Response Parsing class
 * Format:
 *  <?xml version="1.0" encoding="utf-8"?>
 *  <soap:Envelope xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/">
 *      <soap:Body>
 *          <UserLoginResponse xmlns="http://virus-box/MLogger">
 *              <UserLoginResult>long</UserLoginResult>
 *          </UserLoginResponse>
 *      </soap:Body>
 *  </soap:Envelope>
 */
public class XML_Login_Response implements XML_Response {
    
    /**
    * Extracted sessionID.
    */
    private int sessionID;
    
    /**
    * Constructor for use by network layer
    * @param data String retrieved from server (complete XML)
    */
    XML_Login_Response(String data) {
        this.sessionID = XML_Login_Response.PARSING_ERROR;
        try {
            // get root
            Element root = DocumentBuilderFactory.newInstance().newDocumentBuilder().parse(new ByteArrayInputStream(data.getBytes())).getDocumentElement();
            root.normalize();
            // turn root into node
            Node node = root;
            // get Session ID
            this.sessionID = Integer.parseInt(node.getFirstChild().getFirstChild().getFirstChild().getFirstChild().getNodeValue());
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
    * Returns the success of the operation
    * @return true if valid sessionID recovered, else false
    */
    public boolean success() {
        return this.sessionID > 0;
    }
    
    /**
    * Response status.
    * @return the response status. (see XML_Response for error codes)
    */
    public int status() {
        return success() ? 1 : this.sessionID;
    }
    
    /**
    * Returns the extracted SessionID
    * @return The extracted SessionID (or 0 if invalid/etc).
    */
    public int sessionID() {
        return success() ? this.sessionID : 0;
    }
}
