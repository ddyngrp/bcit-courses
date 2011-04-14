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
	private static final String CHANNEL = "channel";
	private static final String ITEM = "item";
	private static final String TITLE = "title";
	private static final String LINK = "link";
	private static final String DESCRIPTION = "description";
	private static final String PUB_DATE = "pubDate";
	private static final String PUB_DATE_ALT = "dc:date";
	
	private boolean isItem = false;
	private boolean isChannel = false;

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
		
		if (localName.equalsIgnoreCase(CHANNEL))
			isChannel = true;
		
		if (localName.equalsIgnoreCase(ITEM)){
			currentFeedItem = new RssArticle();
			isItem = true;
		}
	}

	@Override
	public void endElement(String uri, String localName, String name)
			throws SAXException {
		super.endElement(uri, localName, name);

		if (currentFeed != null && isChannel && !isItem) {
			if (localName.equalsIgnoreCase(TITLE) && builder.toString().trim().length() > 0)
				currentFeed.setName(builder.toString().trim());
			else if (localName.equalsIgnoreCase(LINK) && builder.toString().trim().length() > 0)
				currentFeed.setLink(builder.toString().trim());
			else if (localName.equalsIgnoreCase(DESCRIPTION) && builder.toString().trim().length() > 0)
				currentFeed.setDescription(builder.toString().trim());
			else if (localName.equalsIgnoreCase(CHANNEL))
				isChannel = false;
		}
		
		if (currentFeedItem != null && isItem) {
			if (localName.equalsIgnoreCase(TITLE))
				currentFeedItem.setTitle(builder.toString().trim());
			else if (localName.equalsIgnoreCase(LINK))
				currentFeedItem.setLink(builder.toString().trim());
			else if (localName.equalsIgnoreCase(DESCRIPTION))
				currentFeedItem.setDescription(builder.toString().trim());
			else if (localName.equalsIgnoreCase(PUB_DATE))
				currentFeedItem.setPubDate(builder.toString().trim());
			else if (localName.equalsIgnoreCase(PUB_DATE_ALT))
				currentFeedItem.setPubDate(builder.toString().trim());
			else if (localName.equalsIgnoreCase(ITEM)) {
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
