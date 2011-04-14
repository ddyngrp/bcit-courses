/**
 * Project: Project_RSS_Reader
 * File: ListFeed.java
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
 * @author Steffen L. Norgren, A00683006
 *
 */
public class FeedAdapter extends ArrayAdapter<Feed> {
	private int resource;
	private Context context;
	
	public FeedAdapter(Context context, int resource, ArrayList<Feed> feeds) {
		super(context, resource, feeds);
		this.context = context;
		this.resource = resource;
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		LinearLayout feedView;
		Feed feed = getItem(position);
		
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
