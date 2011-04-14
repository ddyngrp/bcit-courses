/**
Project: Project_RSS_Reader
 * File: FeedItems.java
 * Date: 2011-04-12
 * Time: 6:11:58 PM
 */
package org.trollop.RssReader;

import java.net.MalformedURLException;
import java.net.URL;

import android.os.Parcel;
import android.os.Parcelable;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class FeedItem implements Parcelable {
	private String title;
	private URL link;
	private String description;
	private String pubDate;
	
	public FeedItem() {
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
	
	public static final Parcelable.Creator<FeedItem> CREATOR = new Parcelable.Creator<FeedItem>() {

		@Override
		public FeedItem createFromParcel(Parcel source) {
			return null;
		}

		@Override
		public FeedItem[] newArray(int size) {
			return null;
		}
	};

	@Override
	public int describeContents() {
		return 0;
	}

	@Override
	public void writeToParcel(Parcel dest, int flags) {
		dest.writeString(title);
		dest.writeString(link.toString());
		dest.writeString(description);
		dest.writeString(pubDate);
	}
}
