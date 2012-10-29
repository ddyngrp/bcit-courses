package org.trollop.WebDatabase;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.EditText;
import android.widget.Toast;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.auth.AuthScope;
import org.apache.http.auth.Credentials;
import org.apache.http.auth.UsernamePasswordCredentials;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.DefaultHttpClient;
import org.json.JSONException;
import org.json.JSONObject;

public class AddMessageView extends Activity implements OnClickListener {
	private EditText editMessage;
	private String postURL = "http://192.168.1.100:3000/posts";
	private String userName = "android";
	private String password = "android";

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.add_message);
        
        findViews();
        setClickListeners();
    }
    
	/** Get a handle to all user interface elements */
	private void findViews() {
		editMessage = (EditText) findViewById(R.id.edit_message);
	}
    
    public void setClickListeners() {
        View addEventButton = findViewById(R.id.add_message_button);
        addEventButton.setOnClickListener(this);
    }

	public void onClick(View view) {
		switch (view.getId()) {
		
    	case R.id.add_message_button:   		
    		// Post the data to the Rails server
    		postMessages();  
    		break;
		}
	}
	
	private void postMessages() {
		DefaultHttpClient httpClient = new DefaultHttpClient();
		Credentials creds = new UsernamePasswordCredentials(userName, password);
		httpClient.getCredentialsProvider().setCredentials(
				new AuthScope(null, -1, AuthScope.ANY_REALM), creds);
		
		HttpPost post = new HttpPost(postURL);
	    JSONObject holder = new JSONObject();
	    JSONObject messageObj = new JSONObject();
	    	    
	    try {	
		    messageObj.put("message", editMessage.getText().toString());
		    
		    holder.put("post", messageObj);
		    
		    Log.e("Post JSON", "Post JSON = " + holder.toString());
		    
	    	StringEntity se = new StringEntity(holder.toString());
	    	post.setEntity(se);
	    	post.setHeader("Content-Type","application/json");
	 	
	    	
	    }
	    catch (UnsupportedEncodingException e) {
	    	Log.e("Error", "" + e);
	        e.printStackTrace();
	    }
	    catch (JSONException js) {
	    	js.printStackTrace();
	    }

	    HttpResponse response = null;
	    
	    try {
	        response = httpClient.execute(post);
	    }
	    catch (ClientProtocolException e) {
	        e.printStackTrace();
	        Log.e("ClientProtocol", "" + e);
	    }
	    catch (IOException e) {
	        e.printStackTrace();
	        Log.e("IO", "" + e);
	    }

	    HttpEntity entity = response.getEntity();
	    
	    if (entity != null) {
	        try {
	            entity.consumeContent();
	        } catch (IOException e) {
	        	Log.e("IO E",""+e);
	            e.printStackTrace();
	        }
	    }

	    Toast.makeText(this, "Your message was successfully uploaded", Toast.LENGTH_LONG).show();
	}
}
