/**
 * Project: Project_RSS_Reader
 * File: RSSItems.java
 * Date: 2011-04-13
 * Time: 7:26:15 PM
 */
package org.trollop.RssReader;

import java.util.ArrayList;

import android.os.Parcel;
import android.os.Parcelable;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class RssArticles extends ArrayList<RssArticle> implements Parcelable {
	private static final long serialVersionUID = -1198598975335080328L;
	
	public RssArticles() {
	}
	
	public RssArticles(Parcel in) {
		readFromParcel(in);
	}
	
	@SuppressWarnings("rawtypes")
	public static final Parcelable.Creator CREATOR = new Parcelable.Creator() {
		public RssArticles createFromParcel(Parcel in) {
			return new RssArticles(in);
		}
		
		public Object[] newArray(int arg0) {
			return null;
		}
	};
	
	public void readFromParcel(Parcel in) {
		this.clear();
		
		/* read the list size */
		int size = in.readInt();
		
		/* order of reading to and writing from the Parcel is imperative */
		for (int i = 0; i < size; i++) {
			RssArticle item = new RssArticle();
			item.setTitle(in.readString());
			item.setLink(in.readString());
			item.setDescription(in.readString());
			item.setPubDate(in.readString());
			this.add(item);
		}
	}

	@Override
	public int describeContents() {
		return 0;
	}

	@Override
	public void writeToParcel(Parcel dest, int flags) {
		int size = this.size();
		
		/* write the list size */
		dest.writeInt(size);
		
		/* order of reading to and writing from the Parcel is imperative */
		for (int i = 0; i < size; i++) {
			RssArticle item = this.get(i);
			dest.writeString(item.getTitle());
			dest.writeString(item.getLink().toString());
			dest.writeString(item.getDescription());
			dest.writeString(item.getPubDate());
		}
	}
}
