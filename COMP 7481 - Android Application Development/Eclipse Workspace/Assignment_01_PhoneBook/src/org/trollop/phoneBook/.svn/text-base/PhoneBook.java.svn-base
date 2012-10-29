/**
 * Project: Assignment_01_PhoneBook
 * File: ContactList.java
 * Date: 2011-02-01
 * Time: 12:11:02 PM
 */
package org.trollop.phoneBook;

import java.util.ArrayList;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnKeyListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import org.trollop.phoneBook.SQLiteDBManager;

/**
 * The Class PhoneBook.
 */
public class PhoneBook extends Activity {
	
	/** The phone_book_help. */
	private TextView phone_book_help;
	
	/** The phone_book_list. */
	private ListView phone_book_list;
	
	/** The phone books. */
	private ArrayList<String> phoneBooks;
	
	/** The phone book list adapter. */
	private ArrayAdapter<String> phoneBookListAdapter;
	
    /**
     * Called when the activity is first created.
     *
     * @param savedInstanceState the saved instance state
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.phone_book_list);
        
        phone_book_help = (TextView)findViewById(R.id.phone_book_help);
        phone_book_list = (ListView)findViewById(R.id.phone_book_list);
        
        phone_book_list.setOnItemClickListener(new OnItemClickListener() {
        	public void onItemClick(AdapterView<?> adapter, View view, int position, long id) {
        		String phoneBook = phone_book_list.getItemAtPosition(position).toString();
        		
        		Intent intent = new Intent(getApplicationContext(), ContactList.class);
        		Bundle bundle = new Bundle();
        		
        		bundle.putString("phoneBook", phoneBook);
        		intent.putExtras(bundle);
        		startActivityForResult(intent, 1);
        	}        	
        });
        
        this.populatePhoneBook();
    }
    
    
    /**
     * Populate phone book.
     */
    private void populatePhoneBook() {
        SQLiteDBManager db = new SQLiteDBManager();
    	
        if (phoneBooks == null) {
        	phoneBooks = new ArrayList<String>(db.getPhoneBooks(this));
        }
        else {
        	phoneBooks.clear();
        	phoneBooks.addAll(db.getPhoneBooks(this));
        }
        
        phoneBookListAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, phoneBooks);
        phone_book_list.setAdapter(phoneBookListAdapter);
        phone_book_list.setTextFilterEnabled(true);
        phoneBookListAdapter.sort(null);
        this.updateView();
    }
    
    /**
     * Update view.
     */
    private void updateView() {
        if (!phoneBooks.isEmpty()) {
        	setTitle("Phone Books - Listing " + phoneBooks.size() + " Phone Books");
        	phone_book_help.setVisibility(View.GONE);
        }
        else {
        	setTitle("Phone Books - No Phone Books Created");
        	phone_book_help.setVisibility(View.VISIBLE);
        }
        
        phoneBookListAdapter.notifyDataSetChanged();
    }
    
    /**
     * New phone book.
     */
    private void newPhoneBook() {
    	final AlertDialog.Builder alert = new AlertDialog.Builder(this);
    	final EditText input = new EditText(this);
    	
    	alert.setView(input);
    	alert.setTitle("New Phone Book");
    	
    	input.setOnKeyListener(new OnKeyListener() {
    		public boolean onKey(View view, int keyCode, KeyEvent event) {
    			if ((event.getAction() == KeyEvent.ACTION_DOWN) &&
    					(keyCode == KeyEvent.KEYCODE_ENTER)) {
    				return true;
    			}
    			return false;
    		}
    	});
    	
    	
    	alert.setPositiveButton("Ok", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
				SQLiteDBManager db = new SQLiteDBManager();
				String value = input.getText().toString().trim();
				
				db.addPhoneBook(getApplicationContext(), value);
				phoneBooks.clear();
				phoneBooks.addAll(db.getPhoneBooks(getApplicationContext()));
				phoneBookListAdapter.sort(null);
				phoneBookListAdapter.notifyDataSetChanged();
				updateView();
				
				Toast.makeText(getApplicationContext(), "Created Phone Book: " + value,
						Toast.LENGTH_SHORT).show();
			}
		});
    	
    	alert.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
				dialog.cancel();
			}
		});
    	
    	alert.show();
    }
    
    /**
     * Delete database.
     */
    private void deleteDatabase() {
    	final AlertDialog.Builder alert = new AlertDialog.Builder(this);
    	alert.setTitle("Delete all Phone Books");
    	alert.setMessage("Are you sure you want to delete every phone book?");
    	
    	alert.setPositiveButton("Yes", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
				SQLiteDBManager db = new SQLiteDBManager();
				
				db.deleteAll(getApplicationContext());
				
				phoneBooks.clear();
				phoneBookListAdapter.notifyDataSetChanged();
				
				Toast.makeText(getApplicationContext(), "Deleted all phone books!",
						Toast.LENGTH_SHORT).show();
				
				updateView();
			}
		});
    	
    	alert.setNegativeButton("No", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
				dialog.cancel();
			}
		});
    	
    	alert.show();
    }
    
    /* (non-Javadoc)
     * @see android.app.Activity#onCreateOptionsMenu(android.view.Menu)
     */
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
    	MenuInflater inflater = getMenuInflater();
    	inflater.inflate(R.menu.phone_book_list_menu, menu);
    	return true;
    }
    
    /* (non-Javadoc)
     * @see android.app.Activity#onOptionsItemSelected(android.view.MenuItem)
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
    	switch (item.getItemId()) {
    	case R.id.add_phone_book:
    		this.newPhoneBook();
    		return true;
    	case R.id.delete_database:
    		this.deleteDatabase();
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
    	populatePhoneBook();
    }
}