package org.trollop.Demo;

import java.util.ArrayList;
import java.util.List;

import org.xml.sax.Attributes;
import org.xml.sax.helpers.DefaultHandler;
import org.xml.sax.SAXException;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class RailsXMLHandler extends DefaultHandler {
	private List<String> messages;
	private String currentValue;
	
	public List<String> getMessages() {
		return this.messages;
	}
	
	@Override
	public void startElement(String uri, String localName, String name, Attributes attributes) throws SAXException {
		if (localName.equals("posts")) {
			messages = new ArrayList<String>();
		}
	}
	
	@Override 
	public void endElement(String uri, String localName, String name) throws SAXException {
		if (localName.equals("message")) {
			messages.add("Message: " + currentValue);
		}
	}
	
	@Override
	public void characters(char[] ch, int start, int length) throws SAXException {
		currentValue = new String(ch, start, length);
	}
}
