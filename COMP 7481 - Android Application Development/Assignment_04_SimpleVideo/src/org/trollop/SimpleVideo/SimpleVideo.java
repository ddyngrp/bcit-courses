/**
 * Project: Assignment_04_Video
 * File: SimpleVideo.java
 * Date: 2011-03-21
 * Time: 3:12:37 AM
 */
package org.trollop.SimpleVideo;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

public class SimpleVideo extends Activity {
	private static final int BUFFER_CAPACITY = 5;
	private static final String SERVER_URL = "http://virtual-void.org/";
	private static final String IMAGE_TYPE = ".gif";

	private JitterBuffer jBuffer;
	private ImageProducer ip;
	
	private Thread ipThread;
	private Thread icThread;
	
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		jBuffer = new JitterBuffer(BUFFER_CAPACITY);
		ip = new ImageProducer(jBuffer, 1, 10, SERVER_URL, IMAGE_TYPE);
		
		ipThread = new Thread(ip);
		
		ipThread.start();
	}
	
	private static class ImageProducer implements Runnable {
		private JitterBuffer jBuffer;
		private int firstImageID;
		private int lastImageID;
		private String URL;
		private String imageType;

		public ImageProducer(JitterBuffer jBuffer, int firstImageID, int lastImageID, String URL, String imageType) {
			this.jBuffer = jBuffer;
			this.firstImageID = firstImageID;
			this.lastImageID = lastImageID;
			this.URL = URL;
			this.imageType = imageType;
		}
		
		@Override
		public void run() {
			int index = 1;
			while (!Thread.currentThread().isInterrupted()) {
				jBuffer.downloadImage(URL + index + imageType, index);
				
				if (index == lastImageID)
					index = firstImageID;
				else
					index++;
				
				try {
					Thread.sleep(100);
				}
				catch (InterruptedException e) {
					Log.e("InterruptedException: run", e.toString());
				}
			}
		}
	}
	
//	private static class ImageConsumer implements Runnable {
//		
//	}
}