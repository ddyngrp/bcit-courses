/**
 * Project: Assignment_01_PhoneBook
 * File: ContactEditor.java
 * Date: 2011-02-02
 * Time: 2:43:20 PM
 */
package org.trollop.phoneBook;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

/**
 * The Class ContactEditor.
 *
 * @author Steffen L. Norgren, A00683006
 */
public class ContactEditor extends Activity {
	
	/** The phone book. */
	private String phoneBook;
	
	/** The contact name. */
	private String contactName;
	
	/** The phone number. */
	private String phoneNumber;
	
	/** The is new. */
	private boolean isNew;
	
	/** The contact name input. */
	private EditText contactNameInput;
	
	/** The phone number input. */
	private EditText phoneNumberInput;
	
	/** The save button. */
	private Button saveButton;
	
	/** The cancel button. */
	private Button cancelButton;

	/* (non-Javadoc)
	 * @see android.app.Activity#onCreate(android.os.Bundle)
	 */
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.contact_editor);
        
        contactNameInput = (EditText)findViewById(R.id.contact_name);
        phoneNumberInput = (EditText)findViewById(R.id.contact_number);
        saveButton = (Button)findViewById(R.id.save);
        cancelButton = (Button)findViewById(R.id.cancel);
        
        saveButton.setOnClickListener(new OnClickListener() {
        	public void onClick(View view) {
        		if (contactNameInput.getText().length() > 0) {
        			SQLiteDBManager db = new SQLiteDBManager();
        			
        			String newContactName = contactNameInput.getText().toString().trim();
        			String newPhoneNumber = phoneNumberInput.getText().toString().trim();
        			
        			if (isNew) {
	        			db.addContact(getApplicationContext(), phoneBook, newContactName, newPhoneNumber);
	        			Toast.makeText(getApplicationContext(), "Added Contact: " + newContactName,
	        					Toast.LENGTH_SHORT).show();
        			}
        			else {
        				db.updateContact(getApplicationContext(),
        						phoneBook, contactName, newContactName, newPhoneNumber);
        			}
        			finish();
        		}
        		else {
        			Toast.makeText(getApplicationContext(), "Cannot save empty contact!",
        					Toast.LENGTH_SHORT).show();
        		}
        	}
        });
        
        cancelButton.setOnClickListener(new OnClickListener() {
        	public void onClick(View view) {
        		finish();
        	}
        });
        
        this.populateContact();        
    }
	
    /**
     * Populate contact.
     */
    private void populateContact() {
        SQLiteDBManager db = new SQLiteDBManager();

        Bundle bundle = getIntent().getExtras();
        isNew = bundle.getBoolean("isNew");
        phoneBook = bundle.getString("phoneBook");
        
        if (!isNew) {
        	contactName = bundle.getString("contactName");
        	phoneNumber = db.getContactNumber(getApplicationContext(), contactName, phoneBook);
        	
        	contactNameInput.setText(contactName);
        	phoneNumberInput.setText(phoneNumber);
        }
        else {
        	this.updateView();
        }
    }

    /**
     * Update view.
     */
    private void updateView() {
        if (!isNew)
        	setTitle(phoneBook + " - Editing " + contactName);
        else
        	setTitle(phoneBook + " - Adding New Contact");
    }
    
    /* (non-Javadoc)
     * @see android.app.Activity#onCreateOptionsMenu(android.view.Menu)
     */
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
    	if (!isNew) {
    		MenuInflater inflater = getMenuInflater();
    		inflater.inflate(R.menu.contact_editor_menu, menu);
    	}
    	return true;
    }
    
    /* (non-Javadoc)
     * @see android.app.Activity#onOptionsItemSelected(android.view.MenuItem)
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
    	switch (item.getItemId()) {
    	case R.id.delete_contact:
    		SQLiteDBManager db = new SQLiteDBManager();
    		db.deleteContact(getApplicationContext(), phoneBook, contactName);
    		Toast.makeText(getApplicationContext(), "Deleted " + contactName + "!",
					Toast.LENGTH_SHORT).show();
    		finish();
    		return true;
    	default:
    		return super.onOptionsItemSelected(item);
    	}
    }
}
