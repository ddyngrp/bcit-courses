/**
 * Project: Project_RSS_Reader
 * File: Feeds.java
 * Date: 2011-04-12
 * Time: 6:11:51 PM
 */
package org.trollop.RssReader;

import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class Feed {
	private String name;
	private URL feedURL;
	private URL link;
	private List<FeedItem> itemList;
	
	public Feed() {
		this.itemList = new ArrayList<FeedItem>();
	}
	
	public void addItem(FeedItem item) {
		itemList.add(item);
	}
	
	public int getItemCount() {
		return itemList.size();
	}

	/**
	 * @return the name
	 */
	public String getName() {
		return name;
	}

	/**
	 * @param name the name to set
	 */
	public void setName(String name) {
		this.name = name;
	}

	/**
	 * @return the feedURL
	 */
	public URL getFeedURL() {
		return feedURL;
	}

	/**
	 * @param feedURL the feedURL to set
	 */
	public void setFeedURL(String feedURL) {
		try {
			this.feedURL = new URL(feedURL);
		} catch (MalformedURLException e) {
			throw new RuntimeException(e);
		}
	}

	/**
	 * @return the itemList
	 */
	public List<FeedItem> getItemList() {
		return itemList;
	}
	
	public FeedItem getItem(int itemID) {
		return itemList.get(itemID);
	}

	public URL getLink() {
		return link;
	}

	public void setLink(String link) {
		try {
			this.link = new URL(link);
		} catch (MalformedURLException e) {
			throw new RuntimeException(e);
		}
	}
}
