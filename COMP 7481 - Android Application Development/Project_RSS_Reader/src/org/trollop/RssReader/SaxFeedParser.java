/**
 * Project: Project_RSS_Reader
 * File: SAXFeedParser.java
 * Date: 2011-04-12
 * Time: 11:27:41 PM
 */
package org.trollop.RssReader;

import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

/**
 * @author Steffen L. Norgren, A00683006
 * 
 */
public class SaxFeedParser {
	private final URL feedURL;

	public SaxFeedParser(String feedUrl) {
		try {
			this.feedURL = new URL(feedUrl);
		} catch (MalformedURLException e) {
			throw new RuntimeException(e);
		}
	}

	protected InputStream getInputStream() {
		try {
			return feedURL.openConnection().getInputStream();
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}

	public RssFeed parse() {
		SAXParserFactory factory = SAXParserFactory.newInstance();
		try {
			SAXParser parser = factory.newSAXParser();
			SaxHandler handler = new SaxHandler();
			parser.parse(this.getInputStream(), handler);
			handler.getFeed().setFeedURL(feedURL.toString());
			return handler.getFeed();
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}

}
