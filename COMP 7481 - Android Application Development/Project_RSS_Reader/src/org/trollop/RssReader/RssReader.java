/**
 * Project: Project_RSS_Reader
 * File: RssReader.java
 * Date: 2011-04-10
 * Time: 3:11:51 AM
 */
package org.trollop.RssReader;

import java.util.ArrayList;

import android.app.ListActivity;
import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ListView;

/**
 * The main entry point into the application. Manages the initial downloading
 * of all RSS feeds and instantiates an ListView adapter to display the list
 * of RSS feeds.
 */
public class RssReader extends ListActivity {
	
	private static final String[] defaultFeeds = {"http://www.osnews.com/files/recent.xml",
												  "http://rss.slashdot.org/Slashdot/slashdot",
												  "http://feeds.boingboing.net/boingboing/iBag",
												  "http://www.macrumors.com/macrumors.xml",
												  "http://minimalmac.com/rss",
												  "http://www.phdcomics.com/gradfeed.php",
												  "http://www.smbc-comics.com/rss.php",
												  "http://www.patheos.com/community/slacktivist/feed/",
												  "http://scienceblogs.com/startswithabang/index.xml",
												  "http://xkcd.com/rss.xml",
												  "http://www.popsci.com/rss.xml"};
	private ArrayList<RssFeed> feeds = null;
	private FeedAdapter feedAdapter;
	private ProgressDialog progressDialog;
	private Runnable initFeeds;
	
    /**
     * Called when the activity is first created.
     *
     * @param savedInstanceState the saved instance state
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setTitle("RSS Feed List");
        
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
    
    /**
     * This method will be called when an item in the list is selected.
     * Subclasses should override. Subclasses can call
     * getListView().getItemAtPosition(position) if they need to access the
     * data associated with the selected item.
     * 
     * @param l The ListView where the click happened
     * @param v The view that was clicked within the ListView
     * @param position The position of the view in the list
     * @param id The row id of the item that was clicked
     */
    @Override
    protected void onListItemClick(ListView l, View v, int position, long id) {
    	super.onListItemClick(l, v, position, id);
    	
    	Intent intent = new Intent(RssReader.this, FeedArticleActivity.class);
    	Bundle bundle = new Bundle();
    	
    	RssArticles item = feeds.get(position).getArticleList();
    	
    	bundle.putParcelable("FEED", item);
    	bundle.putString("FEED_NAME", feeds.get(position).getName());
    	intent.putExtras(bundle);

    	startActivity(intent);
    }
    
    /** 
     * Tells the feedAdapter that the data has changed and dismisses
     * the progress dialog */
    private Runnable updateUI = new Runnable() {
    	@Override
    	public void run() {
    		progressDialog.dismiss();
    		feedAdapter.notifyDataSetChanged();
    	}
    };
    
    /**
     * Initializes the feeds by downloading all the articles within each feed.
     * Parsing of the feeds is handled by a SAX Handler class.
     */
    protected void initFeeds() {
    	try {
        	for (String feed : defaultFeeds) {
                SaxFeedParser sfp = new SaxFeedParser(feed);
                feeds.add(sfp.parse());
                Log.i("initFeeds", "" + feeds.size());
        	}
        	Thread.sleep(500);
    	} catch (Exception e) {
    		Log.e("initDefaultFeeds", e.getMessage());
    	}
    	runOnUiThread(updateUI);
    }
}