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

public class XML_Login_Response implements XML_Response {
        
        protected int sessionID = -2;
        
        
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
         * Constructor for use by network layer
         * @param data String retrieved from server (complete XML)
         */
        XML_Login_Response(String data) {
            Element root;
            Node node;
            NodeList children;
            try {
                // get root
                root = DocumentBuilderFactory.newInstance().newDocumentBuilder().parse(new ByteArrayInputStream(data.getBytes())).getDocumentElement();
                root.normalize();
                    
                // turn root into node
                node = root;
                System.out.println("===== Data Start =====");
                for (node=root; node.hasChildNodes() ; node = node.getFirstChild()) {
                    System.out.println("Found Child");
                }
                System.out.println("Value: " + node.getNodeValue());
                System.out.println("=====  Data End  =====");
                
            } catch (ParserConfigurationException e) {
                System.err.println("Caught ParserConfigurationException: " + e.toString());
            } catch (SAXException e) {
                System.err.println("Caught SAXException: " + e.toString());
            } catch (IOException e) {
                System.err.println("Caught IOException: " + e.toString());
            }
        }
        
        
        public boolean success() {
                return this.sessionID > 0;
        }
        
        public int status() {
                return (this.sessionID > 0) ? 1 : this.sessionID;
        }
        
        public int sessionID() {
                return this.sessionID < 0 ? 0 : this.sessionID;
        }
}
