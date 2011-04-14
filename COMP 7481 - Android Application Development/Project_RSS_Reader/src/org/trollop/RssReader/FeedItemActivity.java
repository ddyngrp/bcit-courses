/**
 * Project: Project_RSS_Reader
 * File: FeedListActivity.java
 * Date: 2011-04-13
 * Time: 4:43:50 PM
 */
package org.trollop.RssReader;

import android.app.ListActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ListView;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class FeedItemActivity extends ListActivity {
	private Feed feed;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        feed = (Feed) getIntent().getSerializableExtra("FEED");
        
        for (FeedItem item : feed.getItemList()) {
        	String something = item.getTitle();
        	something.trim();
        }
    }
    
    @Override
    protected void onListItemClick(ListView l, View v, int position, long id) {
    	super.onListItemClick(l, v, position, id);
    }
}
