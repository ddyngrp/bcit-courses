import java.io.IOException;
import javax.microedition.xml.rpc.*	;
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
	
	protected int sessionID;
	
	/**
	 * Constructor for use by network layer
	 * @param data String retrieved from server (complete XML)
	 */
	XML_Login_Response(String data) {
		// TODO: Implement XML Parsing!
		this.sessionID = 0;
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
	
	/* Parsing!
	public int login_response_status() {
		Node node;
		NodeList children;
		int level = 0;
		try {
			// get root
			Element root = DocumentBuilderFactory.newInstance().newDocumentBuilder().parse(new ByteArrayInputStream(this.data.getBytes())).getDocumentElement();
			root.normalize();
			// turn root into node
			node = root;
			// validate xml
			if (node.getNodeType() != Node.ELEMENT_NODE) {
				System.err.println("Not A Parent: " + level);
				return XML.BAD_XML_TYPE;
			}
			level++;
			if (node.getNodeType() != Node.ELEMENT_NODE) {
				System.err.println("Not A Parent: " + level);
				return XML.BAD_XML_TYPE;
			}
			node = node.getChildNodes().item(0);	// enter body
			level++;
			if (node.getNodeType() != Node.ELEMENT_NODE) {
				System.err.println("Not A Parent: " + level);
				return XML.BAD_XML_TYPE;
			}
			node = node.getChildNodes().item(0);	// enter "UserLoginResponse"
			System.out.println("Type Name: " + node.getNodeName());
			level++;
			if (node.getNodeType() != Node.ELEMENT_NODE) {
				System.err.println("Not A Parent: " + level);
				return XML.BAD_XML_TYPE;
			}
			node = node.getChildNodes().item(0);	// enter either "SessionID" or "LoginError"
			System.out.println("Final Name: "  + node.getNodeName() );
			System.out.println("Final Value: " + node.getNodeValue());
		//} catch (ParserConfigurationException e) {
		} catch (Exception e) {
			System.err.println("Unknown Excecption Caught: " + e.toString());
		//} catch (SAXException e) {
		}
		return XML.BAD_XML_TYPE;
	}
	*/
	
}
