/**
 * Project: Assignment_04_Video
 * File: SimpleVideo.java
 * Date: 2011-03-21
 * Time: 3:12:37 AM
 */
package org.trollop.SimpleVideo;

import android.app.Activity;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.ImageButton;
import android.widget.ImageView;

public class SimpleVideo extends Activity {
	private static final int BUFFER_CAPACITY = 10;
	private static final String SERVER_URL = "http://virtual-void.org/";
	private static final String IMAGE_TYPE = ".gif";
	private static final int FIRST_IMAGE_ID = 1;
	private static final int LAST_IMAGE_ID = 10;
	private static final int PLAY_INTERVAL = 10;
	
	private int currentImageID = FIRST_IMAGE_ID;
	
	private Handler mHandler = new Handler();

	private JitterBuffer jBuffer;
	private ImageView imageView;
	private ImageButton playButton;
	private ImageButton pauseButton;
	private ImageButton forwardButton;
	private ImageButton rewindButton;
	private ImageButton exitButton;
	
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		
		imageView = (ImageView)findViewById(R.id.imageView);
		playButton = (ImageButton)findViewById(R.id.play);
		pauseButton = (ImageButton)findViewById(R.id.pause);
		forwardButton = (ImageButton)findViewById(R.id.forward);
		rewindButton = (ImageButton)findViewById(R.id.rewind);
		exitButton = (ImageButton)findViewById(R.id.exit);

		jBuffer = new JitterBuffer(BUFFER_CAPACITY, SERVER_URL, IMAGE_TYPE);
		
		playButton.setImageResource(android.R.drawable.ic_media_play);
		pauseButton.setImageResource(android.R.drawable.ic_media_pause);
		forwardButton.setImageResource(android.R.drawable.ic_media_next);
		rewindButton.setImageResource(android.R.drawable.ic_media_previous);
		exitButton.setImageResource(android.R.drawable.ic_lock_power_off);
		
		pauseButton.setEnabled(false);
		
		/* set initial image */
		Bitmap bm = new Utility().byteArrayToBitmap(jBuffer.getData(FIRST_IMAGE_ID));
		imageView.setImageBitmap(bm);
		
		playButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				playButton.setEnabled(false);
				pauseButton.setEnabled(true);
				forwardButton.setEnabled(false);
				rewindButton.setEnabled(false);
				
				mHandler.removeCallbacks(playImageSequence);
				mHandler.postDelayed(playImageSequence, PLAY_INTERVAL);				
			}
		});

		pauseButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				playButton.setEnabled(true);
				pauseButton.setEnabled(false);
				forwardButton.setEnabled(true);
				rewindButton.setEnabled(true);
				
				mHandler.removeCallbacks(playImageSequence);
			}
		});
		
		forwardButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				mHandler.removeCallbacks(nextImage);
				mHandler.post(nextImage);
			}
		});
		
		rewindButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				mHandler.removeCallbacks(previousImage);
				mHandler.post(previousImage);
			}
		});
		
		exitButton.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				try {
					jBuffer.endThreads();
					Thread.sleep(100);
					finish();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		});
	}
	
	private Runnable playImageSequence = new Runnable() {

		@Override
		public void run() {
			Bitmap bm = new Utility().byteArrayToBitmap(jBuffer.getData(currentImageID));
			
			imageView.setImageBitmap(bm);
			
			if (currentImageID == LAST_IMAGE_ID)
				currentImageID = FIRST_IMAGE_ID;
			else
				currentImageID++;
			
			mHandler.postDelayed(this, PLAY_INTERVAL);
		}
	};
	
	private Runnable previousImage = new Runnable() {

		@Override
		public void run() {
			if (currentImageID == FIRST_IMAGE_ID)
				currentImageID = LAST_IMAGE_ID;
			else
				currentImageID--;
			
			Bitmap bm = new Utility().byteArrayToBitmap(jBuffer.getData(currentImageID));
			
			imageView.setImageBitmap(bm);
		}
	};
	
	private Runnable nextImage = new Runnable() {

		@Override
		public void run() {
			if (currentImageID == LAST_IMAGE_ID)
				currentImageID = FIRST_IMAGE_ID;
			else
				currentImageID++;
			
			Bitmap bm = new Utility().byteArrayToBitmap(jBuffer.getData(currentImageID));
			
			imageView.setImageBitmap(bm);
		}
	};
}