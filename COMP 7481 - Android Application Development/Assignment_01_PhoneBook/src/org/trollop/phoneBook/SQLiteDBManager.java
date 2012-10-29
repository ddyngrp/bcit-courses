/**
 * Project: Assignment_01_PhoneBook
 * File: SQLiteDBManager.java
 * Date: 2011-02-01
 * Time: 5:11:55 PM
 */

package org.trollop.phoneBook;

import java.util.ArrayList;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;

/**
 * The Class SQLiteDBManager is responsible for managing the SQLite database
 * stored on the Android device.
 * 
 * @author Steffen L. Norgren, A00683006
 */
public class SQLiteDBManager {
	
	/** Each phone book is stored in its own table within this database. */
	private String phoneBookDB = "PhoneBook.db";
	/** an index of phone book tables */
	private String phoneBookIndex = "PhoneBookIndex";
	
	/**
	 * Executes an SQL query.
	 * 
	 * @param context
	 *            the application context
	 * @param sql
	 *            the SQL query to be executed
	 * @return true, if successful
	 */
	private boolean execSQL(Context context, String sql) {
		SQLiteDatabase db = context.openOrCreateDatabase(phoneBookDB, 0, null);
		
		// make sure that the database isn't in use
		if (!db.isOpen())
			return false;
		
		db.beginTransaction();
		try {
			db.execSQL(sql);
			db.setTransactionSuccessful();
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		finally {
			db.endTransaction();
		}
		
		db.close();

		return true;
	}
	
	/**
	 * Creates a new phone book in the database.
	 * 
	 * @param context
	 *            the application context
	 * @param phoneBook
	 *            the name of the new phone book create
	 * @return true, if successful
	 */
	public boolean addPhoneBook(Context context, String phoneBook) {
		// create all necessary tables and entries if they don't exist
		if (!this.execSQL(context, "CREATE TABLE IF NOT EXISTS " + phoneBook.replace(" ", "_")
				+ " (contactName VARCHAR PRIMARY KEY NOT NULL, phoneNumber VARCHAR);")
				|| !this.execSQL(context, "CREATE TABLE IF NOT EXISTS " + phoneBookIndex
				+ " (phoneBook VARCHAR PRIMARY KEY NOT NULL);")
				|| !this.execSQL(context, "INSERT OR IGNORE INTO " + phoneBookIndex
				+ " VALUES('" + phoneBook.replace(" ", "_") + "');"))
			return false;
		else		
			return true;
	}
	
	/**
	 * Drops a phone book table and its associated entry in the index table.
	 * 
	 * @param context
	 *            the application context
	 * @param phoneBook
	 *            the name of the phone book to delete
	 * @return true, if successful
	 */
	public boolean deletePhoneBook(Context context, String phoneBook) {
		// deletes the entry from the index table and drops the associated table
		if (!this.execSQL(context, "DELETE FROM " + phoneBookIndex
				+ " WHERE phoneBook = '" + phoneBook.replace(" ", "_") + "';")
				|| !this.execSQL(context, "DROP TABLE " + phoneBook.replace(" ", "_")))
			return false;
		else
			return true;
	}
	
	/**
	 * Drops all phone books.
	 * 
	 * @param context
	 *            the application context
	 * @param phoneBook
	 *            the name of the phone book to delete
	 */
	public void deleteAll(Context context) {
		context.deleteDatabase(phoneBookDB);
	}
	
	/**
	 * Adds a new contact to the associated phone book.
	 * 
	 * @param context
	 *            the application context
	 * @param phoneBook
	 *            the phone book to which to add a contact
	 * @param contactName
	 *            the contact name
	 * @param phoneNumber
	 *            the contact's phone number
	 * @return true, if successful
	 */
	public boolean addContact(Context context, String phoneBook, String contactName,
			String phoneNumber) {
		if (!this.execSQL(context, "INSERT INTO " + phoneBook.replace(" ", "_")
				+ " VALUES('" + contactName + "', '" + phoneNumber + "');"))
			return false;
		
		return true;
	}
	
	/**
	 * Update an existing contact in the associated phone book.
	 * 
	 * @param context
	 *            the application context
	 * @param phoneBook
	 *            the phone book in which the contact will be updated
	 * @param contactName
	 *            the old contact name
	 * @param newContactName
	 *            the new contact name
	 * @param phoneNumber
	 *            the new phone number of the contact
	 * @return true, if successful
	 */
	public boolean updateContact(Context context, String phoneBook,
			String contactName, String newContactName, String phoneNumber) {
		
		if (!this.execSQL(context, "UPDATE " + phoneBook.replace(" ", "_")
				+ " SET contactName = '" + newContactName + "', phoneNumber = '" + phoneNumber + "'"
				+ " WHERE contactName = '" + contactName + "';"))
			return false;
		
		return true;
	}
	
	/**
	 * Deletes a contact in the associated phone book.
	 * 
	 * @param context
	 *            the application context
	 * @param phoneBook
	 *            the phone book in which the contact will be updated
	 * @param contactName
	 *            the new contact name
	 * @return true, if successful
	 */
	public boolean deleteContact(Context context, String phoneBook, String contactName) {
		if (!this.execSQL(context, "DELETE FROM " + phoneBook.replace(" ", "_")
				+ " WHERE contactName = '" + contactName + "';"))
			return false;
		
		return true;
	}
	
	/**
	 * Gets a list of phone books by querying the the phone book index table
	 * 
	 * @param context
	 *            the application context
	 * @return an ArrayList of the currently active phone books
	 */
	public ArrayList<String> getPhoneBooks(Context context) {
		SQLiteDatabase db = context.openOrCreateDatabase(phoneBookDB, 0, null);
		Cursor dbCursor = null;
		ArrayList<String> phoneBooks = new ArrayList<String>();
		
		// make sure that the database isn't in use
		if (!db.isOpen())
			return null;
		
		db.beginTransaction();
		try {
			dbCursor = db.rawQuery("SELECT * FROM " + phoneBookIndex + ";", null);
			
			int phoneBookIndexCol = dbCursor.getColumnIndex("phoneBook");
			
			if (dbCursor != null) {
				dbCursor.moveToFirst();
				
				// make sure that there's something there
				if (dbCursor.getCount() != 0) {
					// loop through all results
					do {
						phoneBooks.add(dbCursor.getString(phoneBookIndexCol).replace("_", " "));
					} while (dbCursor.moveToNext());
				}
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		finally {
			db.endTransaction();
		}
		
		db.close();
		
		return phoneBooks;
	}
	
	/**
	 * Gets a list of contacts within a specific phone book.
	 * 
	 * @param context
	 *            the application context
	 * @param phoneBook
	 *            the phone book from which to get the contacts
	 * @return a 2d ArrayList containing the contact's ID, name, and phone number on each row
	 */
	public ArrayList<String> getContacts(Context context, String phoneBook) {
		SQLiteDatabase db = context.openOrCreateDatabase(phoneBookDB, 0, null);
		Cursor dbCursor = null;
		ArrayList<String> contacts = new ArrayList<String>();
		
		// make sure that the database isn't in use
		if (!db.isOpen())
			return null;
		
		db.beginTransaction();
		try {
			dbCursor = db.rawQuery("SELECT * FROM " + phoneBook.replace(" ", "_") + ";", null);
			
			int contactNameCol = dbCursor.getColumnIndex("contactName");
			
			if (dbCursor != null) {
				dbCursor.moveToFirst();
				
				// make sure that there's something there
				if (dbCursor.getCount() != 0) {
					// loop through all results
					do {
						contacts.add(dbCursor.getString(contactNameCol));
					} while (dbCursor.moveToNext());
				}
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		finally {
			db.endTransaction();
		}
		
		db.close();
		
		return contacts;
	}
	
	/**
	 * Gets a specific contact number from a phone book.
	 * 
	 * @param context
	 *            the application context
	 * @param contactName
	 *            the name of the contact
	 * @param phoneBook
	 *            the phone book from which to get the contacts
	 * @return a String containing the contact's phone number
	 */
	public String getContactNumber(Context context, String contactName, String phoneBook) {
		SQLiteDatabase db = context.openOrCreateDatabase(phoneBookDB, 0, null);
		Cursor dbCursor = null;
		String contactNumber = null;
		
		// make sure that the database isn't in use
		if (!db.isOpen())
			return null;
		
		db.beginTransaction();
		try {
			dbCursor = db.rawQuery("SELECT phoneNumber FROM " + phoneBook.replace(" ", "_")
					+ " WHERE contactName = '" + contactName + "';", null);
			
			int phoneNumberCol = dbCursor.getColumnIndex("phoneNumber");
			
			if (dbCursor != null) {
				dbCursor.moveToFirst();
				
				// make sure that there's something there
				if (dbCursor.getCount() != 0) {
					// loop through all results
					do {
						contactNumber = dbCursor.getString(phoneNumberCol);
					} while (dbCursor.moveToNext());
				}
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		finally {
			db.endTransaction();
		}
		
		db.close();
		
		return contactNumber;
	}
}