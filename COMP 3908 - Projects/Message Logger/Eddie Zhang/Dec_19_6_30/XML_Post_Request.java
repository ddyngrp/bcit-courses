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
        data.append("<?xml version=\"1.0\"?>\n" +
            "<soap:Envelope xmlns:soap=\"http://www.w3.org/2001/12/soap-envelope\" soap:encodingStyle=\"http://www.w3.org/2001/12/soap-encoding\">\n" +
            "   <soap:Body xmlns:mL=\"http://www.example.org/mLogger\">\n" +
            "       <m:PostMessage>\n" +
            "           <m:SessionID>" + sessionID + "</m:SessionID>\n" +
            "           <m:MessageText>" + mc.getDescription() + "</m:MessageText>\n" +
            "           <m:data xmlns:m='http://www.example.org/mLogger'>\n");
            for (MediaNode node = mc.iterator(); node != null; node=node.next()) {
                data.append("               <" + node.item().type() + ">" + node.item().toBase64() + "</" + node.item().type() + ">\n");
            }
            data.append("           </m:data>\n" +
            "       </m:PostMessage>\n" +
            "   </soap:Body>\n" +
            "</soap:Envelope>");
            System.out.println("\n\nTEST!!!!!\n\n" + data.toString() + "\n\nTEST!!!!!\n\n");
        return data.toString();
    }
}
