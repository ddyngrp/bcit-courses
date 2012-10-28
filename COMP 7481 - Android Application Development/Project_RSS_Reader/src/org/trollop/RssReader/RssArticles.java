/**
 * Project: Project_RSS_Reader
 * File: RssArticles.java
 * Date: 2011-04-13
 * Time: 7:26:15 PM
 */
package org.trollop.RssReader;

import java.util.ArrayList;

import android.os.Parcel;
import android.os.Parcelable;

/**
 * Data container class to allow for a Parcelable ArrayList to be passed between
 * different activities/intents within the application. Basically allows for the
 * ArrayList of articles for a particular RSS feed to be flattened for including
 * within a bundle.
 *
 * @author Steffen L. Norgren, A00683006
 */
public class RssArticles extends ArrayList<RssArticle> implements Parcelable {
	
	private static final long serialVersionUID = -1198598975335080328L;
	
	/**
	 * Instantiates a new RSS article collection.
	 */
	public RssArticles() {
	}
	
	/**
	 * Instantiates a new RSS article collection.
	 *
	 * @param in the Parcel input data
	 */
	public RssArticles(Parcel in) {
		readFromParcel(in);
	}
	
	/** Allows for Parcelable object to be created and returned */
	@SuppressWarnings("rawtypes")
	public static final Parcelable.Creator CREATOR = new Parcelable.Creator() {
		
        /**
         * Create a new instance of the Parcelable class, instantiating it
         * from the given Parcel whose data had previously been written by
         * {@link Parcelable#writeToParcel Parcelable.writeToParcel()}.
         * 
         * @param source The Parcel to read the object's data from.
         * @return Returns a new instance of the Parcelable class.
         */
		public RssArticles createFromParcel(Parcel in) {
			return new RssArticles(in);
		}
		
        /**
         * Create a new array of the Parcelable class.
         * 
         * @param size Size of the array.
         * @return Returns an array of the Parcelable class, with every entry
         * initialized to null.
         */
		public Object[] newArray(int arg0) {
			return null;
		}
	};
	
	/**
	 * Read from parcel and recreate an RssArticle object from the data.
	 *
	 * @param in the Parcel input data to be expanded into an object
	 */
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

    /**
     * Describe the kinds of special objects contained in this Parcelable's
     * marshalled representation.
     *  
     * @return a bitmask indicating the set of special object types marshalled
     * by the Parcelable.
     */
	@Override
	public int describeContents() {
		return 0;
	}

    /**
     * Flatten this object in to a Parcel.
     * 
     * @param dest The Parcel in which the object should be written.
     * @param flags Additional flags about how the object should be written.
     * May be 0 or {@link #PARCELABLE_WRITE_RETURN_VALUE}.
     */
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
