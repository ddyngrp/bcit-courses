/**
 * Project: Project_RSS_Reader
 * File: FeedArticleView.java
 * Date: 2011-04-12
 * Time: 6:13:40 PM
 */
package org.trollop.RssReader;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.webkit.WebView;
import android.widget.TextView;

/**
 * Manages displaying a single article within a WebView and allows the
 * user to load the article's source URL in a new browser session.
 *
 * @author Steffen L. Norgren, A00683006
 */
public class FeedArticleView extends Activity {
	
	private String title;
	private String description;
	private String link;
	private String feedName;

    /**
     * Called when the activity is first created.
     *
     * @param savedInstanceState the saved instance state
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.article);
        
        TextView titleText = (TextView) findViewById(R.id.title);
        WebView webView = (WebView) findViewById(R.id.webview);
        
        Bundle bundle = getIntent().getExtras();
        
        feedName = bundle.getString("FEED_NAME");
        title = bundle.getString("TITLE");
        description = bundle.getString("DESCRIPTION");
		link = bundle.getString("LINK");
		
		setTitle(feedName);
		
		titleText.setText(title);
		webView.loadDataWithBaseURL(null, description, "text/html", "utf-8", null);
		
		/* load the article within the android browser */
		titleText.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				Intent browserIntent = new Intent("android.intent.action.VIEW", Uri.parse(link));
				startActivity(browserIntent);
			}
		});
    }
}
