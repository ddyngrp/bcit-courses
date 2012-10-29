package com.example.internet;

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
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class Internet extends Activity {
	Button btn;
	EditText txtURL;
	EditText txtMessage;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        btn = (Button)findViewById(R.id.Button01);
        txtURL = (EditText)findViewById(R.id.EditText01);
        txtMessage = (EditText)findViewById(R.id.EditText02);
        
        btn.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				String url = txtURL.getText().toString();
				if(url.length()>0)
					connect(url);
			}
		});
    }
    private void connect(String address)
    {
    	try {
			URL url = new URL(address);
			System.out.println(address);
			URLConnection connection = url.openConnection();
			HttpURLConnection httpConnection = (HttpURLConnection)connection;
			int responseCode = httpConnection.getResponseCode();
			if(responseCode == HttpURLConnection.HTTP_OK){
				InputStream in = httpConnection.getInputStream();
				BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(in));
				StringBuilder stringBuilder = new StringBuilder();
				String line = null;
				while((line=bufferedReader.readLine())!=null)
				{
					stringBuilder.append(line+"\n");
				}
				bufferedReader.close();
				txtMessage.setText(stringBuilder.toString());
				in.close();
				
			}
			else{
				txtMessage.setText("Request executed.\n Result: "+httpConnection.getResponseCode());
			}

			
		} catch (MalformedURLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }
    
}