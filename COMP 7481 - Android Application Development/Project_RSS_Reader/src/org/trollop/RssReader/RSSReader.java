package org.trollop.RssReader;

import java.util.ArrayList;
import android.app.ListActivity;
import android.app.ProgressDialog;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

public class RSSReader extends ListActivity {
	private static final String[] defaultFeeds = {"http://www.osnews.com/files/recent.xml",
			"http://www.popsci.com/rss.xml",
			"http://feeds.boingboing.net/boingboing/iBag"};
	private ArrayList<Feed> mFeeds = null;
	private FeedListAdapter mFeedListAdapter;
	private Runnable viewFeeds;
	private ProgressDialog mProgressDialog = null;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        super.setContentView(R.layout.main);
        
        mFeeds = new ArrayList<Feed>();
        this.mFeedListAdapter = new FeedListAdapter(this, R.layout.feed_list, mFeeds);
        setListAdapter(this.mFeedListAdapter);
        
        viewFeeds = new Runnable() {
			@Override
			public void run() {
				initDefaultFeeds();
			}
        };
        
        Thread thread = new Thread(null, viewFeeds, "DownloadFeeds");
        thread.start();
        mProgressDialog = ProgressDialog.show(RSSReader.this, "Please wait...", "Downloading feeds...", true);
    }
    
    private Runnable returnRes = new Runnable() {
		@Override
		public void run() {
			if (mFeeds != null && mFeeds.size() > 0) {
				mFeedListAdapter.notifyDataSetChanged();
				
				for (int i = 0; i < mFeeds.size(); i++) {
					Log.i("returnRes", "" + mFeeds.size());
//					mFeedListAdapter.add(mFeeds.get(i));
					Log.i("returnRes", "" + mFeeds.size());
				}
			}
			mProgressDialog.dismiss();
			mFeedListAdapter.notifyDataSetChanged();
		}
    };
    
    protected void initDefaultFeeds() {
    	try {
        	for (String feed : defaultFeeds) {
                SAXFeedParser sfp = new SAXFeedParser(feed);
                mFeeds.add(sfp.parse());
                Log.i("initFeeds", "" + mFeeds.size());
        	}
        	Thread.sleep(1000);
    	} catch (Exception e) {
    		Log.e("initDefaultFeeds", e.getMessage());
    	}
    	runOnUiThread(returnRes);
    }
    
    private class FeedListAdapter extends ArrayAdapter<Feed> {
    	private ArrayList<Feed> feeds = new ArrayList<Feed>();
    	
    	public FeedListAdapter(Context context, int textViewResourceID, ArrayList<Feed> feeds) {
    		super(context, textViewResourceID, feeds);
    		this.feeds = feeds;
    	}

		@Override
		public View getView(int position, View convertView, ViewGroup parent) {
			View view = convertView;
			
			if (view == null) {
				LayoutInflater li = (LayoutInflater) getSystemService(Context.LAYOUT_INFLATER_SERVICE);
				view = li.inflate(R.layout.feed_list, null);
			}
			
			Feed feed = feeds.get(position);
			
			if (feed != null) {
				TextView topText = (TextView) view.findViewById(R.id.toptext);
				TextView botText = (TextView) view.findViewById(R.id.bottomtext);
				
				if (topText != null)
					topText.setText(feed.getName());
				if (botText != null)
					botText.setText("Something will go here");
			}
			return view;
		}
    }
}