/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

import java.util.TreeSet;
import org.xml.sax.*;
import org.xml.sax.helpers.DefaultHandler;

/**
 *
 * @author A00702683
 */
public class WhenWhereHandler  extends DefaultHandler {

    Program prog;
    boolean when = false;
    boolean where = false;

    boolean category = false;
    boolean title = false;
    boolean desc = false;
   
    
    public TreeSet<Program> whenList = new TreeSet<Program>();
    public TreeSet<Program> whereList = new TreeSet<Program>();
    
    @Override
    public void startElement(String namespaceURI, String localName, String qName, Attributes atts)
    {
        if(qName.equals("programme"))
        {
            int startTime = Integer.parseInt(atts.getValue("start").substring(8, 10));
            if(startTime >= 8 && startTime <11)
            {
                when = true;
                
            }
            
            prog = new Program();
            prog.setStartDate(atts.getValue("start"));
            prog.setEndDate(atts.getValue("stop"));
            
        }
        else if(qName.equals("category"))
        {
            category = true;
        }
        else if(qName.equals("title"))
        {
            title = true;
        }
        else if(qName.equals("desc"))
        {
            desc = true;
        }
    }
    
    @Override
    public void characters(char[] ch, int start, int length)
    {
        String temp;

        temp = new String(ch, start, length);
        if(title)
        {
            prog.setTitle(temp);
        }
        else if(desc)
        {
            prog.setDesc(temp);
        }
        else if(category)
        {
            if(temp.equalsIgnoreCase("news"))
            {
                where = true;
            }
        }
        
    }
    
    @Override
    public void endElement(String uri, String localName, String qName)
    {
        if(qName.equals("programme") && when)
        {
            whenList.add(prog);
            when = false;
        }
        else if(qName.equals("programme") && where)
        {
            whereList.add(prog);
            where = false;
        }
        
        category = false;
        title = false;
        desc = false;
    }
}
