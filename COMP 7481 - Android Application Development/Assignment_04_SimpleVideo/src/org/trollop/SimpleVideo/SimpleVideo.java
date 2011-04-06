/**
 * Project: Assignment_04_Video
 * File: SimpleVideo.java
 * Date: 2011-03-21
 * Time: 3:12:37 AM
 */
package org.trollop.SimpleVideo;

import java.util.TimerTask;

import android.app.Activity;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.os.Handler;
import android.os.SystemClock;
import android.util.Log;
import android.widget.ImageView;

public class SimpleVideo extends Activity {
	private static final int BUFFER_CAPACITY = 10;
	private static final String SERVER_URL = "http://virtual-void.org/";
	private static final String IMAGE_TYPE = ".gif";
	private static final int FIRST_IMAGE_ID = 1;
	private static final int LAST_IMAGE_ID = 10;
	private static final int PLAY_INTERVAL = 10;
	
	private Handler mHandler = new Handler();

	private JitterBuffer jBuffer;
	private ImageView iv;
	
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		jBuffer = new JitterBuffer(BUFFER_CAPACITY, SERVER_URL, IMAGE_TYPE);
		iv = (ImageView)findViewById(R.id.imageView);

		mHandler.removeCallbacks(mUpdateImageView);
		mHandler.postDelayed(mUpdateImageView, PLAY_INTERVAL);
	}
	
	private Runnable mUpdateImageView = new Runnable() {
		int currentImageID = FIRST_IMAGE_ID;

		@Override
		public void run() {
			Bitmap bm = new Utils().byteArrayToBitmap(jBuffer.getData(currentImageID));
			
			iv.setImageBitmap(bm);
			
			if (currentImageID == LAST_IMAGE_ID)
				currentImageID = FIRST_IMAGE_ID;
			else
				currentImageID++;
			
			mHandler.postDelayed(this, PLAY_INTERVAL);
		}
		
	};
}