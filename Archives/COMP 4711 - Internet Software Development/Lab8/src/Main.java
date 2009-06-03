
import java.io.File;
import java.io.IOException;
import java.util.Iterator;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParserFactory;
import org.xml.sax.*;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author jim
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        who();
        when();
        where();
    }
    
    /**
     * Display the title & description of all Dr Who shows on BBC3.
     * How many shows of the total shown on BBC3 pertain to Dr Who?
     * Use the *title* element to test.
     */
    public static void who() {
        WhoHandler wh = new WhoHandler();

        try {
            // Create a builder factory
            SAXParserFactory factory = SAXParserFactory.newInstance();
            factory.setValidating(true);

            // Create the builder and parse the file
            factory.newSAXParser().parse(new File("data\\bbc3.xml"), wh);
        } catch (SAXException e) {
            // A parsing error occurred; the xml input is not valid
        } catch (ParserConfigurationException e) {
        } catch (IOException e) {
        }
        
        System.out.println("### Doctor Who Programmes ###");

        for(Iterator iter = wh.whoList.iterator(); iter.hasNext(); )
        {           
           ((Program)iter.next()).print();
        }

        System.out.println("Found " + wh.whoList.size() + " out of " + wh.totalSize + " Programmes");
        System.out.println();
    }
    
    /**
     * Display the title, description & air time of all shows on between 8 & 11pm (local time) on TVDATA.
     * Order the display by air time, so it looks like a real schedule
     */
    public static void when() {
        WhenWhereHandler wwh = new WhenWhereHandler();

        try {
            // Create a builder factory
            SAXParserFactory factory = SAXParserFactory.newInstance();
            factory.setValidating(true);

            // Create the builder and parse the file
            factory.newSAXParser().parse(new File("data\\tvdata.xml"), wwh);
        } catch (SAXException e) {
            // A parsing error occurred; the xml input is not valid
        } catch (ParserConfigurationException e) {
        } catch (IOException e) {
        }

        System.out.println("### 8-11 Programmes ###");
        System.out.println();
        
        for(Iterator iter = wwh.whenList.iterator(); iter.hasNext(); )
        {           
           ((Program)iter.next()).print();
        }
        
        
    }
    
    /**
     * Display the title, description & air time of all news shows on TVDATA.
     * Use the category element to determine these.
     */
    public static void where() {
        WhenWhereHandler wwh = new WhenWhereHandler();

        try {
            // Create a builder factory
            SAXParserFactory factory = SAXParserFactory.newInstance();
            factory.setValidating(true);

            // Create the builder and parse the file
            factory.newSAXParser().parse(new File("data\\tvdata.xml"), wwh);
        } catch (SAXException e) {
            // A parsing error occurred; the xml input is not valid
        } catch (ParserConfigurationException e) {
        } catch (IOException e) {
        }

        System.out.println("### News Programmes ###");
        System.out.println();

        for (Iterator iter = wwh.whereList.iterator(); iter.hasNext();) {
            ((Program) iter.next()).print();
        }      
        
    }



}
