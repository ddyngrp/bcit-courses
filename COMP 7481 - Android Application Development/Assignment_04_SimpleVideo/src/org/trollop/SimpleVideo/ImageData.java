/**
 * Project: Assignment_04_SimpleVideo
 * File: ImageData.java
 * Date: 2011-03-31
 * Time: 8:06:16 AM
 */
package org.trollop.SimpleVideo;

import java.util.concurrent.Delayed;
import java.util.concurrent.TimeUnit;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class ImageData implements Delayed {
	private byte[] data;
	private int sequence;
	private long lastViewed;
	
	ImageData(byte[] data, int sequence) {
		this.data = data;
		this.sequence = sequence;
		this.lastViewed = System.nanoTime();
	}
	
	public int compareTo(Delayed object) {
		if (this.lastViewed < (((ImageData)object).lastViewed))
			return -1;
		else if (this.lastViewed > (((ImageData)object).lastViewed))
			return 1;
		return 0;
	}
	
	public boolean equals(ImageData object) {
		return ((ImageData)object).lastViewed == this.lastViewed;
	}
	
	public long getDelay(TimeUnit unit) {
		long n = this.lastViewed - System.nanoTime();
		return unit.convert(n, TimeUnit.NANOSECONDS);
	}
	
	public long getLastViewed() {
		return this.lastViewed;
	}
	
	public String toString() {
		return "Image Size: " + data.length + "\nLast Viewed: " + String.valueOf(this.lastViewed);
	}
}
