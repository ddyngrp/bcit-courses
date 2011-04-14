package org.trollop.RssReader;

import java.util.ArrayList;

import android.app.ListActivity;
import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.os.Parcelable;
import android.util.Log;
import android.view.View;
import android.widget.ListView;

public class RssReader extends ListActivity {
	private static final String[] defaultFeeds = {"http://www.osnews.com/files/recent.xml",
												  "http://rss.slashdot.org/Slashdot/slashdot",
												  "http://feeds.boingboing.net/boingboing/iBag"};
	private ArrayList<RssFeed> feeds = null;
	private FeedAdapter feedAdapter;
	private ProgressDialog progressDialog;
	private Runnable initFeeds;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        feeds = new ArrayList<RssFeed>();
        
        feedAdapter = new FeedAdapter(RssReader.this, R.layout.feeds, feeds);
        setListAdapter(feedAdapter);
        
        initFeeds = new Runnable() {
        	@Override
        	public void run() {
        		initFeeds();
        	}
        };
        
        Thread thread = new Thread(null, initFeeds, "DownloadFeeds");
        thread.start();
        progressDialog = ProgressDialog.show(RssReader.this, "Please wait...", "Downloading feeds...", true);
    }
    
	@Override
    protected void onListItemClick(ListView l, View v, int position, long id) {
    	super.onListItemClick(l, v, position, id);
    	
    	Intent intent = new Intent(RssReader.this, FeedItemActivity.class);
    	Bundle bundle = new Bundle();
    	
    	RssArticles item = feeds.get(position).getItemList();
    	
    	bundle.putParcelable("FEED", item);
    	intent.putExtras(bundle);

    	startActivity(intent);
    }
    
    private Runnable updateUI = new Runnable() {
    	@Override
    	public void run() {
    		progressDialog.dismiss();
    		feedAdapter.notifyDataSetChanged();
    	}
    };
    
    protected void initFeeds() {
    	try {
        	for (String feed : defaultFeeds) {
                SaxFeedParser sfp = new SaxFeedParser(feed);
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