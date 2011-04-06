/**
 * Project: Assignment_04_SimpleVideo
 * File: Buffer.java
 * Date: 2011-03-31
 * Time: 7:30:47 AM
 */
package org.trollop.SimpleVideo;

import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.util.Collections;
import java.util.Iterator;
import java.util.Vector;

import android.util.Log;

/**
 * This class implements a buffer that can be used by threads to exchange
 * data. The threads that get blocked because the buffer is full or
 * empty are kept in a queue.
 *
 * @author Steffen L. Norgren, A00683006
 */
public class JitterBuffer {
	private String URL;
	private String imageType;
	
	private boolean running = true;
	
	/** The capacity of the buffer. */
	private int capacity;
	
	/** The elements of the buffer. */
	private Vector<ImageData> elements;
	
	/** The queue of threads waiting until the buffer is not full or empty. */
	private Vector<Thread> queue;
	
	/**
	 * Instantiates a new buffer.
	 *
	 * @param capacity the capacity of the buffer
	 */
	public JitterBuffer(int capacity, String URL, String imageType) {
		this.capacity = capacity;
		this.URL = URL;
		this.imageType = imageType;
		
		elements = new Vector<ImageData>(capacity);
		queue = new Vector<Thread>();
		
		new Thread(new Runnable() {
			@Override
			public void run() {
				while(running) {
					deleteOldestImage();
					try {
						Thread.sleep(2000);
					} catch (InterruptedException e) {
						Log.e("image reaper", e.getMessage());
					}
				}
			}
			
		}).start();
	}
	
	public void endThreads() {
		this.running = false;
	}
	
	/**
	 * Returns the size of the buffer.
	 *
	 * @return the size of the buffer.
	 */
	public int size() {
		return elements.size();
	}
	
	/**
	 * Adds an ImageData element to the end of the buffer. If the buffer is full,
	 * the calling thread will be blocked until another thread removes an element
	 * from the buffer.
	 *
	 * @param element the ImageData to be added to the buffer.
	 */
	private synchronized void putData(ImageData element) {
		Thread caller = Thread.currentThread();
		
		if (elements.size() == capacity) {
			queue.addElement(caller);
			
			while (this.size() == capacity || caller != queue.firstElement()) {
				try {
					wait();
				}
				catch (InterruptedException e) {
					Log.e("InterruptedException: put", e.toString());
				}
			}
			queue.removeElement(caller);
		}
		elements.addElement(element);
		notifyAll();
	}
	
	/**
	 * Retrieves the specified image from the buffer. If the buffer is empty, the
	 * calling thread will be blocked until another thread adds an element to
	 * the buffer.
	 *
	 * @return the byte array that was retrieved from the buffer.
	 */
	public synchronized byte[] getData(int imageID) {
		Thread caller = Thread.currentThread();
		
		if (elements.isEmpty() || findImageByID(imageID) == -1) {
			queue.addElement(caller);
			
			if (elements.isEmpty() || caller != queue.firstElement() || findImageByID(imageID) == -1) {
				try {
					final int startID = imageID;
					new Thread(new Runnable() {
						@Override
						public void run() {
							downloadImage(URL + startID + imageType, startID);
						}
						
					}).start();
					
					wait();
				}
				catch (InterruptedException e) {
					Log.e("InterruptedException: get", e.toString());
				}
			}
			queue.removeElement(caller);
		}
		
		int getID = findImageByID(imageID);
		elements.get(getID).updateAccessTime();
		
		notifyAll();
		return elements.get(getID).getData();
	}
	
	private int findImageByID(int imageID) {
		Collections.sort(elements);
		Iterator<ImageData> itr = elements.iterator();
		
		while(itr.hasNext()) {
			ImageData id = itr.next();

			if (id.getImageID() == imageID) {
				return elements.indexOf(id);
			}
		}
		
		return -1;
	}
	
	public synchronized void deleteOldestImage() {
		Thread caller = Thread.currentThread();
		
		if (elements.size() != capacity) {
			queue.addElement(caller);
			
			while ((this.size() != capacity || caller != queue.firstElement()) && running) {
				try {
					wait(100);
				}
				catch (InterruptedException e) {
					Log.e("InterruptedException: put", e.toString());
				}
			}
			queue.removeElement(caller);
		}
		
		Collections.sort(elements, ImageData.AccessTimeComparator);
		elements.remove(0);
	}
	
	public void downloadImage(String URL, int imageID) {
		InputStream is = openHttpConnection(URL);
		Utils util = new Utils();
		
		ImageData id = new ImageData(util.streamToByteArray(is), imageID);
		putData(id);
		
		try {
			is.close();
		}
		catch (IOException e) {
			Log.e("IOException: downloadImage", e.getMessage());
		}
	}
	
	private InputStream openHttpConnection(String URL) {
		InputStream is = null;
		int resCode = -1;

		try {
			URL url = new URL(URL);
			URLConnection urlConn = url.openConnection();

			if (!(urlConn instanceof HttpURLConnection))
				throw new IOException("URL is not an HTTP URL");

			HttpURLConnection httpConn = (HttpURLConnection) urlConn;
			httpConn.setAllowUserInteraction(false);
			httpConn.setInstanceFollowRedirects(true);
			httpConn.setRequestMethod("GET");
			httpConn.connect();

			resCode = httpConn.getResponseCode();

			if (resCode == HttpURLConnection.HTTP_OK) {
				is = httpConn.getInputStream();
			}
		} catch (MalformedURLException e) {
			Log.e("MalformedURLException", e.toString());
		} catch (IOException e) {
			Log.e("IOException", e.toString());
		}

		return is;
	}
}
