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
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class Utils {
	
	public Utils() {
	}
	
	public byte[] streamToByteArray(InputStream is) {
		ByteArrayOutputStream bos = new ByteArrayOutputStream();
		
		try {
			Bitmap bm = BitmapFactory.decodeStream(is);
			bm.compress(Bitmap.CompressFormat.PNG, 0, bos);
			
			byte[] byteArray = bos.toByteArray();
			
			bos.flush();
			bos.close();
			
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
	
	public String timeMillisToString(long timeMillis) {
		Calendar cal = Calendar.getInstance();
		DateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS");

		cal.setTimeInMillis(timeMillis);
		
		return df.format(cal.getTime());
	}
}
