/**
 * Project: Assignment_04_SimpleVideo
 * File: ImageData.java
 * Date: 2011-03-31
 * Time: 8:06:16 AM
 */
package org.trollop.SimpleVideo;


/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class ImageData {
	private int imageID;
	private byte[] data;
	
	
	public ImageData(byte[] data, int imageID) {
		this.data = data;
		this.imageID = imageID;
	}
	
	public void setData(byte[] data) {
		this.data = data;
	}
	
	public void setImageID(int imageID) {
		this.imageID = imageID;
	}
	
	public int getImageID() {
		return this.imageID;
	}
	
	public byte[] getData() {
		return this.data;
	}
}
