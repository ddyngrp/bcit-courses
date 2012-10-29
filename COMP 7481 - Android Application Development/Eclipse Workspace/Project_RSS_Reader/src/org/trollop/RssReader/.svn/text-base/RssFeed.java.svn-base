/**
 * Project: Project_RSS_Reader
 * File: Feeds.java
 * Date: 2011-04-12
 * Time: 6:11:51 PM
 */
package org.trollop.RssReader;

import java.net.MalformedURLException;
import java.net.URL;

/**
 * Data container class for a particular RSS Feed and it's child articles.
 *
 * @author Steffen L. Norgren, A00683006
 */
public class RssFeed {
	
	private String name;
	private String description;
	private URL feedURL;
	private URL link;
	private RssArticles itemList;
	
	/**
	 * Instantiates a new RSS feed.
	 */
	public RssFeed() {
		this.itemList = new RssArticles();
	}
	
	/**
	 * Adds a new article to the RSS feed's article list
	 *
	 * @param item the article to be added
	 */
	public void addItem(RssArticle item) {
		itemList.add(item);
	}
	
	/**
	 * Gets the article count.
	 *
	 * @return the article count
	 */
	public int getItemCount() {
		return itemList.size();
	}

	/**
	 * Gets the name of the RSS feed.
	 *
	 * @return the name of the RSS feed
	 */
	public String getName() {
		return name;
	}

	/**
	 * Sets the name of the RSS feed.
	 *
	 * @param name of the RSS feed to be set
	 */
	public void setName(String name) {
		this.name = name;
	}

	/**
	 * Gets the RSS feed's URL
	 *
	 * @return the feedURL
	 */
	public URL getFeedURL() {
		return feedURL;
	}

	/**
	 * Sets the RSS feed's URL
	 *
	 * @param feedURL the RSS feed's URL to set
	 */
	public void setFeedURL(String feedURL) {
		try {
			this.feedURL = new URL(feedURL);
		} catch (MalformedURLException e) {
			throw new RuntimeException(e);
		}
	}

	/**
	 * Gets the list of articles for the current RSS feed.
	 *
	 * @return the list of articles for the current RSS feed
	 */
	public RssArticles getArticleList() {
		return itemList;
	}
	
	/**
	 * Gets an individual article from the list of articles.
	 *
	 * @param articleID of the article (position within the ArrayList)
	 * @return the article
	 */
	public RssArticle getArticle(int articleID) {
		return itemList.get(articleID);
	}

	/**
	 * Gets base site's URL, which differs from the feed URL.
	 *
	 * @return the URL to the base site.
	 */
	public URL getLink() {
		return link;
	}

	/**
	 * Sets the link for the base site.
	 *
	 * @param link for the base site
	 */
	public void setLink(String link) {
		try {
			this.link = new URL(link);
		} catch (MalformedURLException e) {
			throw new RuntimeException(e);
		}
	}

	/**
	 * Gets the description of the RSS feed.
	 *
	 * @return the description
	 */
	public String getDescription() {
		return description;
	}

	/**
	 * Sets the description of the RSS feed.
	 *
	 * @param description the new description
	 */
	public void setDescription(String description) {
		this.description = description;
	}
}
