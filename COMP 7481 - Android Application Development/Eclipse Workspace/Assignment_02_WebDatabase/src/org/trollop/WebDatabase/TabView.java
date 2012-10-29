package org.trollop.WebDatabase;

import android.app.TabActivity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Window;
import android.widget.TabHost;

public class TabView extends TabActivity {

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE); 

        final TabHost tabHost = getTabHost();

        tabHost.addTab(tabHost.newTabSpec("tab1")
                .setIndicator("Messages")
                .setContent(new Intent(this, WebDatabase.class)));

        tabHost.addTab(tabHost.newTabSpec("tab2")
                .setIndicator("Add Message")
                .setContent(new Intent(this, AddMessageView.class)));
    }
}
