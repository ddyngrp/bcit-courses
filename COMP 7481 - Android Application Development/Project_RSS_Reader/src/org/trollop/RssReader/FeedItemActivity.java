/**
 * Project: Project_RSS_Reader
 * File: FeedListActivity.java
 * Date: 2011-04-13
 * Time: 4:43:50 PM
 */
package org.trollop.RssReader;

import android.app.ListActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ListView;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class FeedItemActivity extends ListActivity {
	RssArticles rssItems;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        Bundle bundle = getIntent().getExtras();
        rssItems = bundle.getParcelable("FEED");
    }
    
    @Override
    protected void onListItemClick(ListView l, View v, int position, long id) {
    	super.onListItemClick(l, v, position, id);
    }
}
