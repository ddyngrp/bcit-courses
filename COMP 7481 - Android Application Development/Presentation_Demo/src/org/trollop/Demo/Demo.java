package org.trollop.Demo;

import java.net.URL;
import java.util.List;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.InputSource;
import org.xml.sax.XMLReader;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.widget.LinearLayout;
import android.widget.TextView;

public class Demo extends Activity {
	private static final String xmlURL = "http://trollop.org:3000/posts?format=xml";
	private RailsXMLHandler railsXMLHandler;
	private List<String> messages;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        /** Create a new layout to display the view */
        LinearLayout layout = new LinearLayout(this);
        layout.setOrientation(1);
        
        /** Create a new TextView array to display the results */
        TextView messageView[];
        
        try {
        	/** Handling XML */
        	SAXParserFactory spf = SAXParserFactory.newInstance();
        	SAXParser sp = spf.newSAXParser();
        	XMLReader xr = sp.getXMLReader();
        	
        	/** Send URL to parse XML tags */
        	URL sourceURL = new URL(xmlURL);
        	
        	/** Create handler to handle XML tags */
        	railsXMLHandler = new RailsXMLHandler();
        	xr.setContentHandler(railsXMLHandler);
        	xr.parse(new InputSource(sourceURL.openStream()));
        }
        catch (Exception e) {
        	Log.e("XML Error", e.getMessage());
        }
        
        /** Get result from the handler */
        messages = railsXMLHandler.getMessages();
        
        /** Assign TextView array length by ArrayList size */
        messageView = new TextView[messages.size()];
        
        /** Set the result text in TextView and add it to the layout */
        for (int i = 0; i < messages.size(); i++) {
        	messageView[i] = new TextView(this);
        	messageView[i].setText(messages.get(i));
        	layout.addView(messageView[i]);
        }
        
        /** set the layout view to display */
        setContentView(layout);
    }
}