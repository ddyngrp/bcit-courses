/**
 * Project: Project_RSS_Reader
 * File: SAXHandler.java
 * Date: 2011-04-12
 * Time: 11:27:56 PM
 */
package org.trollop.RssReader;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

/**
 * @author Steffen L. Norgren, A00683006
 * 
 */
public class SAXHandler extends DefaultHandler {
	private static final String ITEM = "item";
	private static final String TITLE = "title";
	private static final String LINK = "link";
	private static final String DESCRIPTION = "description";
	private static final String PUB_DATE = "pubDate";
	
	private boolean isItem = false;

	private Feed currentFeed;
	private FeedItem currentFeedItem;
	private String currentNode;

	public Feed getFeed() {
		return this.currentFeed;
	}

	@Override
	public void characters(char[] ch, int start, int length)
			throws SAXException {
		super.characters(ch, start, length);
		
		currentNode = new String(ch, start, length);
	}

	@Override
	public void startElement(String uri, String localName, String name,
			Attributes attributes) throws SAXException {
		super.startElement(uri, localName, name, attributes);
		
		if (localName.equalsIgnoreCase(ITEM)){
			this.currentFeedItem = new FeedItem();
			this.isItem = true;
		}
	}

	@Override
	public void endElement(String uri, String localName, String name)
			throws SAXException {
		super.endElement(uri, localName, name);

		if (this.currentFeed != null) {
			if (localName.equalsIgnoreCase(TITLE) && !isItem)
				currentFeed.setName(currentNode);
			else if (localName.equalsIgnoreCase(LINK) && !isItem)
				currentFeed.setLink(currentNode);
		}
		
		if (this.currentFeedItem != null) {
			if (localName.equalsIgnoreCase(TITLE) && isItem)
				currentFeedItem.setTitle(currentNode);
			else if (localName.equalsIgnoreCase(LINK) && isItem)
				currentFeedItem.setLink(currentNode);
			else if (localName.equalsIgnoreCase(DESCRIPTION) && isItem)
				currentFeedItem.setDescription(currentNode);
			else if (localName.equalsIgnoreCase(PUB_DATE) && isItem)
				currentFeedItem.setPubDate(currentNode);
			else if (localName.equalsIgnoreCase(ITEM) && isItem) {
				currentFeed.addItem(currentFeedItem);
				isItem = false;
			}
		}
	}

	@Override
	public void startDocument() throws SAXException {
		super.startDocument();
		
		this.currentFeed = new Feed();
	}
}
