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
        
        protected static final int SUCCESS = 0;
        protected static final int INVALID_SESSION_ID = 1;
        protected static final int UNKNOWN_SERVER_ERROR = 2;
        protected static final int XML_PARSING_ERROR = 3;
        
        protected int status;
        
        XML_Post_Response(String data) {
                //Element root = DocumentBuilderFactory.newInstance().newDocumentBuilder().parse(is).getDocumentElement();
                //root.normalize();
                this.status = 3;
        }
        
        public boolean success() {
                return this.status == 0;
        }
        
        public int status() {
                return this.status;
        }
}
