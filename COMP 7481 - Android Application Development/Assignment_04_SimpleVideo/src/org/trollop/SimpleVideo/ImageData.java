/**
 * Project: Assignment_04_SimpleVideo
 * File: ImageData.java
 * Date: 2011-03-31
 * Time: 8:06:16 AM
 */
package org.trollop.SimpleVideo;

import java.util.Comparator;

import android.graphics.Bitmap;
import android.util.Log;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class ImageData implements Comparable<ImageData> {
	private int imageID;
	private byte[] data;
	private long accessTime;

	public ImageData(byte[] data, int imageID) {
		this.data = data;
		this.imageID = imageID;
		this.accessTime = System.currentTimeMillis();
	}

	public void setData(byte[] data) {
		this.data = data;
	}

	public void setImageID(int imageID) {
		this.imageID = imageID;
	}

	public void updateAccessTime() {
		this.accessTime = System.currentTimeMillis();
	}

	public int getImageID() {
		return this.imageID;
	}

	public byte[] getData() {
		return this.data;
	}

	public long getAccessTime() {
		return this.accessTime;
	}

	public void logInfo() {
		Utility util = new Utility();
		Bitmap bm;

		bm = util.byteArrayToBitmap(this.data);

		Log.i("ImageInfo", "Size: " + this.data.length);
		Log.i("ImageInfo", "Dimensions: " + bm.getWidth() + "x" + bm.getHeight());
		Log.i("ImageInfo", "Access Time: " + util.timeMillisToString(this.accessTime));
	}

	@Override
	public int compareTo(ImageData compareImageData) {

		if (this.imageID > compareImageData.getImageID()) {
			return 1;
		}
		else if (this.imageID < compareImageData.getImageID()) {
			return -1;
		}
		return 0;
	}
	
	public static Comparator<ImageData> AccessTimeComparator = new Comparator<ImageData>() {

		@Override
		public int compare(ImageData imageData1, ImageData imageData2) {
			if (imageData1.getAccessTime() > imageData2.getAccessTime()) {
				return 1;
			}
			else if (imageData1.getAccessTime() < imageData2.getAccessTime()) {
				return -1;
			}
			
			return 0;
		}
	};
}
