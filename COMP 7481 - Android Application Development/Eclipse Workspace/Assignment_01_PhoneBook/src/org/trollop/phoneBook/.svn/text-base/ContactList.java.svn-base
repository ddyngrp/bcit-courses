/**
 * Project: Assignment_01_PhoneBook
 * File: ContactList.java
 * Date: 2011-02-02
 * Time: 2:43:02 PM
 */
package org.trollop.phoneBook;

import java.util.ArrayList;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.AdapterView.OnItemClickListener;

// TODO: Auto-generated Javadoc
/**
 * The Class ContactList.
 *
 * @author Steffen L. Norgren, A00683006
 */
public class ContactList extends Activity {
	
	/** The phone book. */
	private String phoneBook;
	
	/** The contact_list_help. */
	private TextView contact_list_help;
	
	/** The contact_list. */
	private ListView contact_list;
	
	/** The contacts. */
	private ArrayList<String> contacts;
	
	/** The contacts adapter. */
	private ArrayAdapter<String> contactsAdapter;

	/* (non-Javadoc)
	 * @see android.app.Activity#onCreate(android.os.Bundle)
	 */
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.contact_list);
        
        contact_list_help = (TextView)findViewById(R.id.contact_list_help);
        contact_list = (ListView)findViewById(R.id.contact_list);
        
        contact_list.setOnItemClickListener(new OnItemClickListener() {
        	public void onItemClick(AdapterView<?> adapter, View view, int position, long id) {
        		String contactName = contact_list.getItemAtPosition(position).toString();
        		
        		Intent intent = new Intent(getApplicationContext(), ContactEditor.class);
        		Bundle bundle = new Bundle();
        		
        		bundle.putString("phoneBook", phoneBook);
        		bundle.putString("contactName", contactName);
        		bundle.putBoolean("isNew", false);
        		intent.putExtras(bundle);
        		
        		startActivityForResult(intent, 1);
        	}        	
        });
        
        this.populateContacts();        
    }
	
    /**
     * Populate contacts.
     */
    private void populateContacts() {
        SQLiteDBManager db = new SQLiteDBManager();

        Bundle bundle = getIntent().getExtras();
        phoneBook = bundle.getString("phoneBook");
        
        if (contacts == null) {
        	contacts = new ArrayList<String>(db.getContacts(this, phoneBook));
        }
        else {
        	contacts.clear();
        	contacts.addAll(db.getContacts(this, phoneBook));
        }
        contactsAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, contacts);
        contact_list.setAdapter(contactsAdapter);
        contact_list.setTextFilterEnabled(true);
        contactsAdapter.sort(null);
        this.updateView();
    }

    /**
     * Update view.
     */
    private void updateView() {
        if (!contacts.isEmpty()) {
        	setTitle(phoneBook + " - Listing " + contacts.size() + " Contacts");
        	contact_list_help.setVisibility(View.GONE);
        }
        else {
        	setTitle(phoneBook + " - No Contacts Created");
        	contact_list_help.setVisibility(View.VISIBLE);
        }
        contactsAdapter.notifyDataSetChanged();
    }
    
    /* (non-Javadoc)
     * @see android.app.Activity#onCreateOptionsMenu(android.view.Menu)
     */
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
    	MenuInflater inflater = getMenuInflater();
    	inflater.inflate(R.menu.contact_list_menu, menu);
    	return true;
    }
    
    /* (non-Javadoc)
     * @see android.app.Activity#onOptionsItemSelected(android.view.MenuItem)
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
    	switch (item.getItemId()) {
    	case R.id.add_contact:
    		Intent intent = new Intent(getApplicationContext(), ContactEditor.class);
    		Bundle bundle = new Bundle();
    		
    		bundle.putString("phoneBook", phoneBook);
    		bundle.putBoolean("isNew", true);
    		intent.putExtras(bundle);
    		
    		startActivityForResult(intent, 1);

    		return true;
    	case R.id.delete_phone_book:
    		SQLiteDBManager db = new SQLiteDBManager();
    		db.deletePhoneBook(getApplicationContext(), phoneBook);
    		Toast.makeText(getApplicationContext(), "Deleted Phone Book: " + phoneBook,
					Toast.LENGTH_SHORT).show();
    		finish();
    		return true;
    	default:
    		return super.onOptionsItemSelected(item);
    	}
    }
    
    /* (non-Javadoc)
     * @see android.app.Activity#onActivityResult(int, int, android.content.Intent)
     */
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
    	populateContacts();
    }
}
