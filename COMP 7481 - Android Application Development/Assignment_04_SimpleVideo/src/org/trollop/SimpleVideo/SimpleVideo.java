/**
 * Project: Assignment_04_Video
 * File: SimpleVideo.java
 * Date: 2011-03-21
 * Time: 3:12:37 AM
 */
package org.trollop.SimpleVideo;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.ImageView;

public class SimpleVideo extends Activity {
	private Bitmap bitmap = null;
	
	/** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        downloadImageSequence("http://virtual-void.org/", 10, "gif");
    }
    
	public void downloadImageSequence(String baseURL, int numImages, String type) {
		final String url = baseURL;
		
		new Thread() {
			public void run() {
				InputStream in = null;
				Message msg = Message.obtain();
				
				try {
					in = openHttpConnection(url);
					bitmap = BitmapFactory.decodeStream(in);
					Bundle b = new Bundle();
					b.putParcelable("bitmap", bitmap);
					msg.setData(b);
					in.close();
				}
				catch (IOException e) {
					Log.e("IOException", e.toString());
				}
				
				messageHandler.sendMessage(msg);
			}
		}.start();
	}

	private InputStream openHttpConnection(String URL) {
		InputStream in = null;
		int resCode = -1;
		
		try {
			URL url = new URL(URL);
			URLConnection urlConn = url.openConnection();
			
			if (!(urlConn instanceof HttpURLConnection))
				throw new IOException("URL is not an HTTP URL");

			HttpURLConnection httpConn = (HttpURLConnection)urlConn;
			httpConn.setAllowUserInteraction(false);
			httpConn.setInstanceFollowRedirects(true);
			httpConn.setRequestMethod("GET");
			httpConn.connect();
			
			resCode = httpConn.getResponseCode();
			
			if (resCode == HttpURLConnection.HTTP_OK) {
				in = httpConn.getInputStream();
			}
		}
		catch (MalformedURLException e) {
			Log.e("MalformedURLException", e.toString());
		}
		catch (IOException e) {
			Log.e("IOException", e.toString());
		}
		
		return in;
	}
	
	/* adds data to the buffer */
	public boolean addData(byte[] image, int size) {
		return false;
	}
	
	/* get data from the buffer */
	public byte[] getData() {
		return null;
	}
	
//	/* puts data into the buffer */
//	private Handler messageHandler = new Handler() {
//		public void handleMessage(Message msg) {
//			super.handleMessage(msg);
//			
//			ImageView img = (ImageView) findViewById(R.id.imageView);
//			
//			ByteArrayOutputStream baos = new ByteArrayOutputStream();
//			bitmap = (Bitmap)(msg.getData().getParcelable("bitmap"));
//			
//			bitmap.compress(Bitmap.CompressFormat.PNG, 0, baos);
//			byte[] b = baos.toByteArray();
//			
//			img.setImageBitmap(BitmapFactory.decodeByteArray(b, 0, b.length));
//			
//			//img.setImageBitmap((Bitmap)(msg.getData().getParcelable("bitmap")));
//		}
//	};
}