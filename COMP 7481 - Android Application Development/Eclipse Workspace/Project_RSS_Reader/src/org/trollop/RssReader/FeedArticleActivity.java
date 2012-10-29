/**
 * Project: Project_RSS_Reader
 * File: FeedArticleActivity.java
 * Date: 2011-04-13
 * Time: 4:43:50 PM
 */
package org.trollop.RssReader;

import android.app.ListActivity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ListView;

/**
 * Manages and displays the articles within a single feed.
 *
 * @author Steffen L. Norgren, A00683006
 */
public class FeedArticleActivity extends ListActivity {
	
	private RssArticles rssItems;
	private FeedArticleAdapter feedItemAdapter;
	private String feedName;

    /**
     * Called when the activity is first created.
     *
     * @param savedInstanceState the saved instance state
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        /* retrieve the ArrayList of articles for the current feed */
        Bundle bundle = getIntent().getExtras();
        rssItems = bundle.getParcelable("FEED");
        feedName = bundle.getString("FEED_NAME");
        
        setTitle(feedName);
        
        feedItemAdapter = new FeedArticleAdapter(FeedArticleActivity.this, R.layout.article_list, rssItems);
        setListAdapter(feedItemAdapter);
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
    	
    	Intent intent = new Intent(FeedArticleActivity.this, FeedArticleView.class);
    	Bundle bundle = new Bundle();
    	
    	/* place data within the bundle to be accessed by the new activity */
    	bundle.putString("FEED_NAME", feedName);
    	bundle.putString("TITLE", rssItems.get(position).getTitle());
    	bundle.putString("DESCRIPTION", rssItems.get(position).getDescription());
    	bundle.putString("LINK", rssItems.get(position).getLink().toString());
    	
    	intent.putExtras(bundle);

    	startActivity(intent);
    }
}
