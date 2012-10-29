/**
 * Project: Project_RSS_Reader
 * File: FeedAdapter.java
 * Date: 2011-04-12
 * Time: 6:13:23 PM
 */
package org.trollop.RssReader;

import java.util.ArrayList;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.LinearLayout;
import android.widget.TextView;

/**
 * Manages displaying RSS Feed items within a ListView. Because we're
 * extending the ArrayAdapter class, we can automatically display new
 * data items within the ListView.
 *
 * @author Steffen L. Norgren, A00683006
 */
public class FeedAdapter extends ArrayAdapter<RssFeed> {
	
	private int resource;
	private Context context;
	
	/**
	 * Instantiates a new FeedAdapter object.
	 *
	 * @param context application's current context
	 * @param resource id of the current list item
	 * @param feeds to be displayed within the ListView
	 */
	public FeedAdapter(Context context, int resource, ArrayList<RssFeed> feeds) {
		super(context, resource, feeds);
		this.context = context;
		this.resource = resource;
	}

    /**
     * Get a View that displays the data at the specified position in the data set. You can either
     * create a View manually or inflate it from an XML layout file. When the View is inflated, the
     * parent View (GridView, ListView...) will apply default layout parameters unless you use
     * {@link android.view.LayoutInflater#inflate(int, android.view.ViewGroup, boolean)}
     * to specify a root view and to prevent attachment to the root.
     * 
     * @param position The position of the item within the adapter's data set of the item whose view
     *        we want.
     * @param convertView The old view to reuse, if possible. Note: You should check that this view
     *        is non-null and of an appropriate type before using. If it is not possible to convert
     *        this view to display the correct data, this method can create a new view.
     * @param parent The parent that this view will eventually be attached to
     * @return A View corresponding to the data at the specified position.
     */
	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		LinearLayout feedView;
		RssFeed feed = getItem(position);
		
		if (convertView == null) {
			feedView = new LinearLayout(context);
			String inflater = Context.LAYOUT_INFLATER_SERVICE;
			LayoutInflater vi;
			vi = (LayoutInflater) context.getSystemService(inflater);
			vi.inflate(resource, feedView, true);
		}
		else {
			feedView = (LinearLayout) convertView;
		}
		
		if (feed != null) {
			TextView topText = (TextView) feedView.findViewById(R.id.toptext);
			TextView botText = (TextView) feedView.findViewById(R.id.bottomtext);
			
			if (topText != null) {
				topText.setText(feed.getName());
			}
			if (botText != null)
				botText.setText(feed.getDescription());
		}
		return feedView;
	}
}
