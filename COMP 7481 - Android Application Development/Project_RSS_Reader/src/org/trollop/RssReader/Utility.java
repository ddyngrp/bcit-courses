/**
 * Project: Assignment_04_SimpleVideo
 * File: Utility.java
 * Date: 2011-04-06
 * Time: 1:23:17 AM
 */
package org.trollop.RssReader;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.util.Log;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class Utility {
	
	public Utility() {
	}
	
	public Bitmap streamToBitmap(InputStream is) {
		ByteArrayOutputStream bos = new ByteArrayOutputStream();
		
		try {
			Bitmap bm = BitmapFactory.decodeStream(is);
			bm.eraseColor(Color.TRANSPARENT);
			bm.compress(Bitmap.CompressFormat.PNG, 0, bos);
			
			bos.flush();
			bos.close();
			
			return bm;
		}
		catch (IOException e) {
			Log.e("IOException: bitmapToByteArray", "Error compressing to byte stream");
			return null;
		}
	}
}
