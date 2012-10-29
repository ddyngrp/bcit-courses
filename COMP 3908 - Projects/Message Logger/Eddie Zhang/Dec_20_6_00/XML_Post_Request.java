/*
 * XML_Post_Request.java
 *
 * MLogger, 2008
 * Confidential and proprietary.
 */
 package src;
import java.io.IOException;
import javax.microedition.xml.rpc.* ;
import java.io.InputStream;
import java.io.ByteArrayInputStream;
import net.rim.device.api.xml.parsers.DocumentBuilderFactory;
import org.w3c.dom.Element;
import net.rim.device.api.xml.parsers.ParserConfigurationException;
import org.xml.sax.SAXException;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import net.rim.device.api.crypto.CryptoException;
import java.lang.StringBuffer;

public class XML_Post_Request implements XML_Request {
    
    protected MediaController mc;
    protected int sessionID;
    
    XML_Post_Request(MediaController mc, int sessionID) {
        this.mc = mc;
        this.sessionID = sessionID;
    }
    
    public String toString() {
        StringBuffer data = new StringBuffer();
        data.append("<?xml version=\"1.0\" encoding=\"utf-8\"?>" +
        "<soap:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\">" +
            "<soap:Body>" +
                "<DougXML xmlns=\"http://virus-box/MLogger\">" +
                    "<sessionID>" + mc.sessionID() + "</sessionID>" +
                    "<title>" + mc.title() + "</title>" +
                    "<message>" + mc.description() + "</message>");
        for (MediaNode node = mc.iterator(); node != null; node = node.next()) {
            data.append("<dataType>" + node.item().format() + "</dataType>" +
                    "<data>" + node.item().toBase64() + "</data>");
        }
        data.append("</DougXML>" +
            "</soap:Body>" +
        "</soap:Envelope>");
        return data.toString();
    }
}
