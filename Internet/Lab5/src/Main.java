/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

import org.jdom.*;
import org.jdom.output.*;
import org.jdom.input.*;
import java.util.*;

/**
 *
 * @author jim, Steffen L. Norgren
 */
public class Main {

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
        int drWhoCount = 0;
        SAXBuilder jdomObj = new SAXBuilder();
        org.jdom.Document doc = jdomObj.build("data/bbc3.xml");

        Element root = doc.getRootElement();
        List shows = root.getChildren();

        for (Iterator i = shows.iterator(); i.hasNext();) {
            Element e = (Element) i.next();
            if (e.getChild("title").getValue().toLowerCase()
                    .contains("Doctor Who".toLowerCase())) {

                drWhoCount++; // increment the number of Doctor Who shows

                // Print out the title and description
                String title = e.getChild("title").getValue();
                String description = e.getChild("desc").getValue();
                System.out.println("Title: " + title + "\nDescription: "
                        + description + "\n");
            }
        }
        System.out.println(drWhoCount + " of " + shows.size() +
                " shows on BBC3 pertain to Dr Who\n");
    }

    /**
     * Display the title, description & air time of all shows on between 8 &
     * 11pm (local time) on TVDATA. Order the display by air time, so it looks
     * like a real schedule
     * NOTE: The times in the XML file are betwen midnight and 10:30 AM
     *       I will assume you meant between 8 & 11 AM.
     */
    public static void when() throws Exception {
        SAXBuilder jdomObj = new SAXBuilder();
        org.jdom.Document doc = jdomObj.build("data/tvdata.xml");

        Element root = doc.getRootElement();
        List shows = root.getChildren("programme");

        for (Iterator i = shows.iterator(); i.hasNext();) {
            Element e = (Element) i.next();

            String start = e.getAttribute("start").getValue();
            String startHour = start.substring(8, 10);
            String startMin = start.substring(10, 12);
            int hourInt = Integer.parseInt(startHour);
            int minInt = Integer.parseInt(startMin);

            if ((hourInt > 8 && hourInt < 11)
                    || (hourInt > 11 && minInt == 0)) {
                System.out.print("Title: ");
                System.out.print(e.getChild("title").getValue());
                System.out.print("\nDescription: ");
                if (e.getChild("desc") != null) {
                    System.out.print(e.getChild("desc").getValue());
                }
                System.out.println("\nStart Time: " + startHour + ":"
                        + startMin + "\n");
            }
        }
    }

    /**
     * Display the title, description & air time of all news shows on TVDATA.
     * Use the category element to determine these.
     */
    public static void where() throws Exception {
        SAXBuilder jdomObj = new SAXBuilder();
        org.jdom.Document doc = jdomObj.build("data/tvdata.xml");

        Element root = doc.getRootElement();
        List shows = root.getChildren("programme");

        for (Iterator i = shows.iterator(); i.hasNext();) {
            Element e = (Element) i.next();
            List categories = e.getChildren("category");

            String start = e.getAttribute("start").getValue();
            String startHour = start.substring(8, 10);
            String startMin = start.substring(10, 12);

            for (Iterator it = categories.iterator(); it.hasNext(); ) {
                Element el = (Element) it.next();

                if (el.getValue().toLowerCase().contains("news".toLowerCase())) {
                System.out.print("Title: ");
                System.out.print(e.getChild("title").getValue());
                System.out.print("\nDescription: ");
                if (e.getChild("desc") != null) {
                    System.out.print(e.getChild("desc").getValue());
                }
                System.out.println("\nStart Time: " + startHour + ":"
                        + startMin + "\n");
                }
            }
        }
    }
}
