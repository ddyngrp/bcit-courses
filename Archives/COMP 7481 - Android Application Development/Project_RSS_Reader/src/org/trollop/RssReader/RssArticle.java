/**
Project: Project_RSS_Reader
 * File: RssArticle.java
 * Date: 2011-04-12
 * Time: 6:11:58 PM
 */
package org.trollop.RssReader;

import java.net.MalformedURLException;
import java.net.URL;

/**
 * Data class for individual articles from within a single RSS feed.
 *
 * @author Steffen L. Norgren, A00683006
 */
public class RssArticle {
	
	private String title;
	private URL link;
	private String description;
	private String pubDate;
	
	/**
	 * Instantiates a new RSS article.
	 */
	public RssArticle() {
	}
	
	/**
	 * Gets the article's title.
	 *
	 * @return the title
	 */
	public String getTitle() {
		return title;
	}

	/**
	 * Sets the article's title.
	 *
	 * @param title the title to set
	 */
	public void setTitle(String title) {
		this.title = title;
	}

	/**
	 * Gets the link to the article.
	 *
	 * @return the link
	 */
	public URL getLink() {
		return link;
	}

	/**
	 * Sets the link to the article.
	 *
	 * @param link the link to set
	 */
	public void setLink(String link) {
		try {
			this.link = new URL(link);
		} catch (MalformedURLException e) {
			throw new RuntimeException(e);
		}
	}

	/**
	 * Gets the actual article text.
	 *
	 * @return the article's text
	 */
	public String getDescription() {
		return description;
	}

	/**
	 * Sets the article's text.
	 *
	 * @param article's text to set
	 */
	public void setDescription(String description) {
		this.description = description;
	}

	/**
	 * Gets the publication date.
	 *
	 * @return the pubDate
	 */
	public String getPubDate() {
		return pubDate;
	}

	/**
	 * Sets the publication date.
	 *
	 * @param pubDate the pubDate to set
	 */
	public void setPubDate(String pubDate) {
		this.pubDate = pubDate;
	}
}