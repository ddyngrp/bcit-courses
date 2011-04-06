/**
 * Project: Assignment_04_SimpleVideo
 * File: ImageData.java
 * Date: 2011-03-31
 * Time: 8:06:16 AM
 */
package org.trollop.SimpleVideo;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.Serializable;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;


/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class ImageData implements Comparable<Object>, Serializable {
	private static final long serialVersionUID = 601898220926582662L;
	private int imageID;
	private byte[] data;
	private long accessTime;
	
	ImageData(byte[] data, int imageID) {
		this.data = data;
		this.imageID = imageID;
		this.accessTime = System.nanoTime();
	}
	
	public int getImageID() {
		return this.imageID;
	}
	
	public Bitmap getImage() {
		return BitmapFactory.decodeByteArray(this.data, 0, this.data.length);
	}
	
	public boolean setData(byte[] data, int size) {
		return false;
	}
	
	public boolean setImage(InputStream is) {
		ByteArrayOutputStream bos = new ByteArrayOutputStream();
		
		try {
			Bitmap bm = BitmapFactory.decodeStream(is);
			bm.compress(Bitmap.CompressFormat.PNG, 0, bos);
			
			

			bos.flush();
			bos.close();
			is.close();
			
			return true;
		}
		catch (IOException e) {
			Log.e("BITMAP_TEST", "Error compressing to byte stream");
			return false;
		}
	}

	public long getAccessTime() {
		return this.accessTime;
	}
	
	@Override
	public int compareTo(Object another) {
		return 0;
	}
	
	@Override
	public String toString() {
		return "Image Size: " + data.length + "\nAccess Time (ns): " + this.accessTime;
	}
}
