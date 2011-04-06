/**
 * Project: Assignment_04_SimpleVideo
 * File: Utility.java
 * Date: 2011-04-06
 * Time: 1:23:17 AM
 */
package org.trollop.SimpleVideo;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class Utility {
	
	public Utility() {
	}
	
	public byte[] streamToByteArray(InputStream is) {
		ByteArrayOutputStream bos = new ByteArrayOutputStream();
		
		try {
			Bitmap bm = BitmapFactory.decodeStream(is);
			bm.compress(Bitmap.CompressFormat.PNG, 0, bos);
			
			byte[] byteArray = bos.toByteArray();
			
			bos.flush();
			bos.close();
			is.close();
			
			return byteArray;
		}
		catch (IOException e) {
			Log.e("IOException: bitmapToByteArray", "Error compressing to byte stream");
			return null;
		}
	}
	
	public Bitmap byteArrayToBitmap(byte[] data) {
		Bitmap bm = BitmapFactory.decodeByteArray(data, 0, data.length);
		
		return bm;
	}
}
