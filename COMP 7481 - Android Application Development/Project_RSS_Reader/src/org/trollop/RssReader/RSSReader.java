package org.trollop.RssReader;

import java.util.ArrayList;
import java.util.List;

import android.app.ListActivity;
import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.BaseAdapter;
import android.widget.LinearLayout;
import android.widget.ListAdapter;
import android.widget.TextView;

public class RSSReader extends ListActivity {
	private static final String[] defaultFeeds = {"http://www.osnews.com/files/recent.xml",
			"http://www.popsci.com/rss.xml",
			"http://feeds.boingboing.net/boingboing/iBag"};
	private List<Feed> feeds;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        super.setContentView(R.layout.main);
        
        initDefaultFeeds();
        
        ListAdapter adapter = new FeedListAdapter(this);
        getListView().setAdapter(adapter);
    }
    
    protected void initDefaultFeeds() {
    	feeds = new ArrayList<Feed>();
    	
    	for (String feed : defaultFeeds) {
            SAXFeedParser sfp = new SAXFeedParser(feed);
            feeds.add(sfp.parse());
    	}
    }
    
    private class FeedListAdapter extends BaseAdapter {
    	private Context mContext;
    	
    	public FeedListAdapter(Context context) {
    		mContext = context;
    	}

		@Override
		public int getCount() {
			return feeds.size();
		}

		@Override
		public Object getItem(int position) {
			return feeds.get(position);
		}

		@Override
		public long getItemId(int position) {
			return position;
		}

		@Override
		public View getView(int position, View convertView, ViewGroup parent) {
			LinearLayout itemLayout;
			Feed feed = feeds.get(position);
			
			
			itemLayout = (LinearLayout) LayoutInflater.from(mContext).inflate(R.layout.feed_list, parent, false);
			
			TextView topText = (TextView) findViewById(R.id.toptext);
			TextView botText = (TextView) findViewById(R.id.bottomtext);
			
			if (topText != null && botText != null) {
				topText.setText(feed.getName());
				botText.setText("Testing bottom...");
			}
			
			return itemLayout;
		}
    }
}