/**
 * Project: Project_RSS_Reader
 * File: FeedItems.java
 * Date: 2011-04-12
 * Time: 6:11:58 PM
 */
package org.trollop.RssReader;

import java.net.MalformedURLException;
import java.net.URL;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class FeedItem {
	private String title;
	private URL link;
	private String description;
	private String pubDate;
	private boolean unread;
	
	public FeedItem() {
		this.unread = true;
	}
	
	/**
	 * @return the title
	 */
	public String getTitle() {
		return title;
	}

	/**
	 * @param title the title to set
	 */
	public void setTitle(String title) {
		this.title = title;
	}

	/**
	 * @return the link
	 */
	public URL getLink() {
		return link;
	}

	/**
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
	 * @return the description
	 */
	public String getDescription() {
		return description;
	}

	/**
	 * @param description the description to set
	 */
	public void setDescription(String description) {
		this.description = description;
	}

	/**
	 * @return the pubDate
	 */
	public String getPubDate() {
		return pubDate;
	}

	/**
	 * @param pubDate the pubDate to set
	 */
	public void setPubDate(String pubDate) {
		this.pubDate = pubDate;
	}

	/**
	 * @return the unread
	 */
	public boolean isUnread() {
		return unread;
	}

	/**
	 * @param unread the unread to set
	 */
	public void setUnread(boolean unread) {
		this.unread = unread;
	}
}
