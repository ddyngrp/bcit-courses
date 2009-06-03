/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

import java.util.LinkedList;
import java.util.List;
import org.xml.sax.*;
import org.xml.sax.helpers.DefaultHandler;

/**
 *
 * @author A00702683
 */
public class WhoHandler extends DefaultHandler {

    Program prog;
    String tmp;
    
    boolean title = false;
    boolean desc = false;
    
    boolean who = false;
    
    public List<Program> whoList = new LinkedList<Program>();
    public int totalSize = 0;
    
    
    
    @Override
    public void startElement(String namespaceURI, String localName, String qName, Attributes atts)
    {
        if(qName.equals("title"))
            title = true;
        else if(qName.equals("desc"))
            desc = true;
    }
    
    @Override
    public void characters(char[] ch, int start, int length)
    {
        String temp;

        temp = new String(ch, start, length);

        if(title)
        {
            if(temp.contains("Doctor Who"))
            {
                who = true;
                prog = new Program();
                prog.setTitle(temp);
                prog.setDesc(tmp);
            }
        }
        else if(desc)
        {
            tmp = temp;
        }
    }

    @Override
    public void endElement(String uri, String localName, String qName)
    {
        if(qName.equals("programme"))
        {
            if(who)
            {
                whoList.add(prog);
                who = false;
            }
            
            totalSize++;
        }
        
        title = false;
        desc = false;
    }


}
