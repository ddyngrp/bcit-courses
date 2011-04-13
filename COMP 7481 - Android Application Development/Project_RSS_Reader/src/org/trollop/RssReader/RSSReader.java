package org.trollop.RssReader;

import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.os.Bundle;
import android.widget.ImageView;

public class RSSReader extends Activity {
	private static final String[] defaultFeeds = {"http://www.osnews.com/files/recent.xml",
			"http://www.popsci.com/rss.xml",
			"http://feeds.boingboing.net/boingboing/iBag"};
//	private static final String[] defaultFeeds = {"http://www.popsci.com/rss.xml"};
	
	
	private List<Feed> feeds;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        ImageView iv = (ImageView) findViewById(R.id.imageView1);
        
        initDefaultFeeds();
        
        iv.setImageBitmap(feeds.get(0).getIcon());
    }
    
    private void initDefaultFeeds() {
    	feeds = new ArrayList<Feed>();
    	
    	for (String feed : defaultFeeds) {
            SAXFeedParser sfp = new SAXFeedParser(feed);
            feeds.add(sfp.parse());
    	}
    }
}