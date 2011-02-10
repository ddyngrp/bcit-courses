package org.trollop.http;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;

import android.app.Activity;
import android.os.Bundle;
import android.text.Html;
import android.text.Spanned;
import android.view.MotionEvent;
import android.view.View;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.EditText;

public class http extends Activity {
	private EditText txtURL;
	private Button btnLoad;
	private WebView webView;

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		txtURL = (EditText)findViewById(R.id.text_address);
		btnLoad = (Button)findViewById(R.id.button_load);
		webView = (WebView)findViewById(R.id.webview);
		
		webView.getSettings().setJavaScriptEnabled(true);
		
		/***
		 * Disable navigation within the webview
		 */
		webView.setOnTouchListener(new View.OnTouchListener() {
			public boolean onTouch(View v, MotionEvent event) {
				return true;
			}
		});

		btnLoad.setOnClickListener(new View.OnClickListener() {

			public void onClick(View v) {
				String url = txtURL.getText().toString();
				if (url.length() > 0)
					connect(url);
			}
		});
	}

	private void connect(String address) {
		try {
			URL url = new URL(address);
			System.out.println(address);
			URLConnection connection = url.openConnection();
			HttpURLConnection httpConnection = (HttpURLConnection) connection;
			int responseCode = httpConnection.getResponseCode();
			
			if (responseCode == HttpURLConnection.HTTP_OK) {
				InputStream in = httpConnection.getInputStream();
				BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(in));
				StringBuilder stringBuilder = new StringBuilder();
				String line = null;
				
				while ((line = bufferedReader.readLine()) != null) {
					stringBuilder.append(line + "\n");
				}
				
				bufferedReader.close();
				webView.loadData(stringBuilder.toString(), "text/html", "utf8");
				in.close();
			} else {
				webView.loadData("Request executed.\n Result: "
						+ httpConnection.getResponseCode(), "text/html", "utf8");
			}

		} catch (MalformedURLException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}