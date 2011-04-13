package org.trollop.RssReader;

import android.app.Activity;
import android.os.Bundle;

public class RSSReader extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        SAXFeedParser sfp = new SAXFeedParser("http://www.osnews.com/files/recent.xml");
        sfp.parse();
    }
}