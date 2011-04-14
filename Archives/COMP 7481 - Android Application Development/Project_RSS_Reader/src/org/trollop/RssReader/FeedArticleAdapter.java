/**
 * Project: Project_RSS_Reader
 * File: FeedArticleAdapter.java
 * Date: 2011-04-12
 * Time: 6:13:32 PM
 */
package org.trollop.RssReader;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.LinearLayout;
import android.widget.TextView;

/**
 * Manages displaying RSS articles from a single feed within a ListView.
 *
 * @author Steffen L. Norgren, A00683006
 */
public class FeedArticleAdapter extends ArrayAdapter<RssArticle> {
	
	private int resource;
	private Context context;
	
	/**
	 * Instantiates a new FeedArticleAdapter object.
	 *
	 * @param context application's current context
	 * @param resource id of the current list item
	 * @param feeds to be displayed within the ListView
	 */
	public FeedArticleAdapter(Context context, int resource, RssArticles articles) {
		super(context, resource, articles);
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
		RssArticle article = getItem(position);
		
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
		
		if (article != null) {
			TextView title = (TextView) feedView.findViewById(R.id.article_title);
			
			if (title != null) {
				title.setText(article.getTitle());
			}
		}
		return feedView;
	}
}
