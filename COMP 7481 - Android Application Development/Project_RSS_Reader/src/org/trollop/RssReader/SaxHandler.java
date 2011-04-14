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
public class SaxHandler extends DefaultHandler {
	private static final String ITEM = "item";
	private static final String TITLE = "title";
	private static final String LINK = "link";
	private static final String DESCRIPTION = "description";
	private static final String PUB_DATE = "pubDate";
	private static final String PUB_DATE_ALT = "dc:date";
	
	private boolean isItem = false;

	private RssFeed currentFeed;
	private RssArticle currentFeedItem;
	private StringBuilder builder;

	public RssFeed getFeed() {
		return currentFeed;
	}

	@Override
	public void characters(char[] ch, int start, int length)
			throws SAXException {
		super.characters(ch, start, length);
		
		builder.append(ch, start, length);
	}

	@Override
	public void startElement(String uri, String localName, String name,
			Attributes attributes) throws SAXException {
		super.startElement(uri, localName, name, attributes);
		
		if (localName.equalsIgnoreCase(ITEM)){
			currentFeedItem = new RssArticle();
			isItem = true;
		}
	}

	@Override
	public void endElement(String uri, String localName, String name)
			throws SAXException {
		super.endElement(uri, localName, name);

		if (currentFeed != null && builder.toString().trim().length() > 0) {
			if (localName.equalsIgnoreCase(TITLE) && !isItem)
				currentFeed.setName(builder.toString().trim());
			else if (localName.equalsIgnoreCase(LINK) && !isItem)
				currentFeed.setLink(builder.toString().trim());
			else if (localName.equalsIgnoreCase(DESCRIPTION) && !isItem)
				currentFeed.setDescription(builder.toString().trim());
		}
		
		if (currentFeedItem != null) {
			if (localName.equalsIgnoreCase(TITLE) && isItem)
				currentFeedItem.setTitle(builder.toString().trim());
			else if (localName.equalsIgnoreCase(LINK) && isItem)
				currentFeedItem.setLink(builder.toString().trim());
			else if (localName.equalsIgnoreCase(DESCRIPTION) && isItem)
				currentFeedItem.setDescription(builder.toString().trim());
			else if (localName.equalsIgnoreCase(PUB_DATE) && isItem)
				currentFeedItem.setPubDate(builder.toString().trim());
			else if (localName.equalsIgnoreCase(PUB_DATE_ALT) && isItem)
				currentFeedItem.setPubDate(builder.toString().trim());
			else if (localName.equalsIgnoreCase(ITEM) && isItem) {
				currentFeed.addItem(currentFeedItem);
				isItem = false;
			}
		}
		builder.setLength(0);
	}

	@Override
	public void startDocument() throws SAXException {
		super.startDocument();
		
		currentFeed = new RssFeed();
		builder = new StringBuilder();
	}
}
