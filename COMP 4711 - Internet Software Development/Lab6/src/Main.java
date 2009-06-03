/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

import org.xml.sax.helpers.DefaultHandler;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import org.xml.sax.XMLReader;
import org.xml.sax.InputSource;
import org.xml.sax.Attributes;

/**
 *
 * @author jim, Steffen L. Norgren
 */
public class Main extends DefaultHandler {

    static String what;
    static int drWhoCount = 0,  showCount = 0;
    String title, desc, start, stop, category;
    boolean inChannel = false;
    boolean inProgramme = false;
    boolean inTV = false;
    boolean gotDesc = false;
    boolean gotTitle = false;
    boolean gotCategory = false;

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        try {
            who();
            when();
            where();
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    /**
     * Display the title & description of all Dr Who shows on BBC3.
     * How many shows of the total shown on BBC3 pertain to Dr Who?
     * Use the *title* element to test.
     */
    public static void who() throws Exception {
        XMLReader xmlReader = null;

        try {
            SAXParserFactory spFactory = SAXParserFactory.newInstance();
            SAXParser saxParser = spFactory.newSAXParser();
            xmlReader = saxParser.getXMLReader();
            xmlReader.setContentHandler(new Main());
            InputSource source = new InputSource("data/bbc3.xml");

            what = "who";

            xmlReader.parse(source);

        } catch (Exception e) {
            System.err.println(e);
            System.exit(1);
        }
    }

    /**
     * Display the title, description & air time of all shows on between 8 &
     * 11pm (local time) on TVDATA. Order the display by air time, so it looks
     * like a real schedule
     * NOTE: The times in the XML file are betwen midnight and 10:30 AM
     *       I will assume you meant between 8 & 11 AM.
     */
    public static void when() throws Exception {
        XMLReader xmlReader = null;

        try {
            SAXParserFactory spFactory = SAXParserFactory.newInstance();
            SAXParser saxParser = spFactory.newSAXParser();
            xmlReader = saxParser.getXMLReader();
            xmlReader.setContentHandler(new Main());
            InputSource source = new InputSource("data/tvdata.xml");

            what = "when";

            xmlReader.parse(source);

        } catch (Exception e) {
            System.err.println(e);
            System.exit(1);
        }
    }

    /**
     * Display the title, description & air time of all news shows on TVDATA.
     * Use the category element to determine these.
     */
    public static void where() throws Exception {
        XMLReader xmlReader = null;

        try {
            SAXParserFactory spFactory = SAXParserFactory.newInstance();
            SAXParser saxParser = spFactory.newSAXParser();
            xmlReader = saxParser.getXMLReader();
            xmlReader.setContentHandler(new Main());
            InputSource source = new InputSource("data/tvdata.xml");

            what = "where";

            xmlReader.parse(source);

        } catch (Exception e) {
            System.err.println(e);
            System.exit(1);
        }
    }

    @Override
    public void startElement(String namespaceURI, String localName,
            String qName, Attributes atts) {
        if (qName.equals("channel") && atts.getValue("id").equals("bbc3")) {
            inChannel = true;
        }
        if (qName.equals("tv")) {
            inTV = true;
        }

        if (inChannel && qName.equals("programme")) {
            inProgramme = true;
        }
        if (inTV && qName.equals("programme")) {
            inProgramme = true;
        }

        if (inProgramme) {
            if (atts.getValue("start") != null &&
                    atts.getValue("stop") != null) {
                start = atts.getValue("start");
                stop = atts.getValue("start");
            }

            if (qName.equals("desc")) {
                gotDesc = true;
            } else if (qName.equals("title")) {
                gotTitle = true;
            } else if (qName.equals("category")) {
                gotCategory = true;
            }
        }
    }

    @Override
    public void endElement(String uri, String localName, String qName) {
        if (qName.equals("channel")) {
            inChannel = false;

            if (what.equals("who")) {
                System.out.println("\n" + drWhoCount + " of " + showCount +
                        " shows on BBC3 pertain to Dr Who\n");
            }

        }
        if (qName.equals("tv")) {
            inTV = false;
        }

        if (inChannel && qName.equals("programme")) {
            inProgramme = false;

            if (title.contains("Doctor Who") && what.equals("who")) {
                System.out.print(title + desc);
                title = "";
                desc = "";
                drWhoCount++;
                showCount++;
            } else if (what.equals("who")) {
                title = "";
                desc = "";
                showCount++;
            }
        }
        if (inTV && qName.equals("programme")) {
            inProgramme = false;

            String startHour = start.substring(8, 10);
            String startMin = start.substring(10, 12);
            int hourInt = Integer.parseInt(startHour);
            int minInt = Integer.parseInt(startMin);

            if (what.equals("when") &&
                    ((hourInt > 8 && hourInt < 11) ||
                    (hourInt > 11 && minInt == 0))) {
                if (!title.contains("null")) {
                    System.out.print(title);
                }
                if (!desc.contains("null")) {
                    System.out.print(desc);
                }
                System.out.println("Start Time: " + startHour + ":" + startMin);
            } else if (what.equals("where") && category.contains("news")) {
                System.out.print(title);
                System.out.print(desc);
                System.out.println("Start Time: " + startHour + ":" + startMin);
            }

            category = "";
            title = "";
            desc = "";
            start = "";
            stop = "";
        }

        if (inProgramme) {
            if (qName.equals("desc")) {
                gotDesc = false;
            } else if (qName.equals("title")) {
                gotTitle = false;
            }
            if (qName.equals("category")) {
                gotCategory = false;
            }
        }
    }

    @Override
    public void characters(char[] ch, int start, int length) {
        if (length > 0) {
            if (gotTitle) {
                title += "\nTitle: " + new String(ch, start, length) + "\n";
                title = title.replace("null", "");
            }
            if (gotDesc) {
                desc += "Description: " + new String(ch, start, length) + "\n";
                title = title.replace("null", "");
            }
            if (gotCategory) {
                category += new String(ch, start, length);
                category = category.toLowerCase();
            }
        }
    }
}
