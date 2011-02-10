package org.trollop.WebDatabase;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.StringReader;
import java.net.Authenticator;
import java.net.PasswordAuthentication;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.ArrayList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.w3c.dom.CharacterData;
import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;

import android.app.ListActivity;
import android.content.Context;
import android.os.Bundle;
import android.sax.Element;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

public class WebDatabase extends ListActivity {
	private ArrayList<Message> messagesArrayList = null;
	private MessageAdapter m_adapter;
	private String userName = "android";
	private String password = "android";

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		messagesArrayList = new ArrayList<Message>();
		retreiveMessages();

		this.m_adapter = new MessageAdapter(this, R.layout.row, messagesArrayList);
		setListAdapter(this.m_adapter);
	}

	private void retreiveMessages() {
		Authenticator.setDefault(new Authenticator() {
			protected PasswordAuthentication getPasswordAuthentication() {
				// couldn't get this to work with the dialog
				return new PasswordAuthentication(userName, password.toCharArray());
			}
		});

		HttpClient httpClient = new DefaultHttpClient();

		String xmlResponse;

		try {
			String url = "http://192.168.1.100:3000/posts?format=xml";
			Log.d("retrieveMessage", "performing get " + url);

			HttpGet method = new HttpGet(new URI(url));
			HttpResponse response = httpClient.execute(method);
			
			if (response != null) {
				xmlResponse = getResponse(response.getEntity());
				messagesArrayList = parseXMLString(xmlResponse);
			}
			else {
				Log.i("retrieveMessage", "got a null response");
			}
		}
		catch (IOException e) {
			Log.e("Error", "IOException " + e.getMessage());
		}
		catch (URISyntaxException e) {
			Log.e("Error", "URISyntaxException " + e.getMessage());
		}

	}

	private String getResponse(HttpEntity entity) {
		String response = "";

		try {
			int length = (int) entity.getContentLength();
			StringBuffer sb = new StringBuffer(length);
			InputStreamReader isr = new InputStreamReader(entity.getContent(), "UTF-8");
			char buff[] = new char[length];
			int cnt;
			
			while ((cnt = isr.read(buff, 0, length - 1)) > 0) {
				sb.append(buff, 0, cnt);
			}

			response = sb.toString();
			isr.close();
		}
		catch (IOException e) {
			e.printStackTrace();
		}

		return response;
	}

	private ArrayList<Message> parseXMLString(String xmlString) {

		try {
			DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
			DocumentBuilder db = dbf.newDocumentBuilder();
			InputSource is = new InputSource();
			is.setCharacterStream(new StringReader(xmlString));

			Document doc = db.parse(is);
			NodeList nodes = doc.getElementsByTagName("post");

			messagesArrayList = new ArrayList<Message>();

			// Iterate the events
			for (int i = 0; i < nodes.getLength(); i++) {
				Element element = (Element)nodes.item(i+1);
				messagesArrayList.add(new Message());

				NodeList messageIDNum = ((Document)element).getElementsByTagName("id");
				Element line = (Element)messageIDNum.item(0);
				messagesArrayList.get(i).messageID = 
					Integer.parseInt(getCharacterDataFromElement(line));

				NodeList message = ((Document)element).getElementsByTagName("message");
				line = (Element)message.item(0);
				messagesArrayList.get(i).message = getCharacterDataFromElement(line).trim();
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		return messagesArrayList;

	}

	public static String getCharacterDataFromElement(Element e) {
		Node child = ((Node) e).getFirstChild();
		if (child instanceof CharacterData) {
			CharacterData cd = (CharacterData) child;
			return cd.getData();
		}
		return "?"; // ListActivity will display a ? if a null value is passed
					// to the Rails server
	}

	private class MessageAdapter extends ArrayAdapter<Message> {

		private ArrayList<Message> items;

		public MessageAdapter(Context context, int textViewResourceId,
				ArrayList<Message> items) {
			super(context, textViewResourceId, items);
			this.items = items;
		}

		@Override
		public View getView(int position, View convertView, ViewGroup parent) {
			View view = convertView;
			if (view == null) {
				LayoutInflater vi =
					(LayoutInflater)getSystemService(Context.LAYOUT_INFLATER_SERVICE);
				view = vi.inflate(R.layout.row, null);
			}
			Message msgObj = items.get(position);
			if (msgObj != null) {
				TextView tt = (TextView)view.findViewById(R.id.toptext);
				TextView bt = (TextView)view.findViewById(R.id.bottomtext);

				if (tt != null) {
					tt.setText("Message: " + msgObj.getMessage());
				}
				if (bt != null) {
					bt.setText("ID: " + msgObj.getMessageID());
				}

			}
			return view;
		}
	}
}