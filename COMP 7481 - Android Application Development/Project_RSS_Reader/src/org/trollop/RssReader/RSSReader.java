package org.trollop.RssReader;

import java.util.ArrayList;

import android.app.Activity;
import android.app.ProgressDialog;
import android.os.Bundle;
import android.util.Log;
import android.widget.ListView;

public class RSSReader extends Activity {
	private static final String[] defaultFeeds = {"http://www.osnews.com/files/recent.xml",
												  "http://rss.slashdot.org/Slashdot/slashdot",
												  "http://feeds.boingboing.net/boingboing/iBag"};
	private ListView feedListView;
	private ArrayList<Feed> feeds = null;
	private FeedList feedListAdapter;
	private ProgressDialog progressDialog;
	private Runnable initFeeds;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        super.setContentView(R.layout.main);
        
        feedListView = (ListView) findViewById(R.id.list_view);
        feeds = new ArrayList<Feed>();
        
        feedListAdapter = new FeedList(RSSReader.this, R.layout.feeds, feeds);
        feedListView.setAdapter(feedListAdapter);
        
        initFeeds = new Runnable() {
        	@Override
        	public void run() {
        		initFeeds();
        	}
        };
        
        Thread thread = new Thread(null, initFeeds, "DownloadFeeds");
        thread.start();
        progressDialog = ProgressDialog.show(RSSReader.this, "Please wait...", "Downloading feeds...", true);
    }
    
    private Runnable updateUI = new Runnable() {
    	@Override
    	public void run() {
    		progressDialog.dismiss();
    		feedListAdapter.notifyDataSetChanged();
    	}
    };
    
    protected void initFeeds() {
    	try {
        	for (String feed : defaultFeeds) {
                SAXFeedParser sfp = new SAXFeedParser(feed);
                feeds.add(sfp.parse());
                Log.i("initFeeds", "" + feeds.size());
        	}
        	Thread.sleep(1000);
    	} catch (Exception e) {
    		Log.e("initDefaultFeeds", e.getMessage());
    	}
    	runOnUiThread(updateUI);
    }
}