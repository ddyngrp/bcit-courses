import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;

public class DBManager {

	String dbName = "tempDB.db";
	
	
	public boolean writeToDB(Context context,String name, String phoneNumber)
	{
		
		SQLiteDatabase db = context.openOrCreateDatabase(dbName, 0, null);
		
		if(!db.isOpen())
			return false;
		
		db.beginTransaction();
		try{
			//create a table
            db.execSQL("CREATE TABLE IF NOT EXISTS "
                                + "PhoneBook"
                                + " (name VARCHAR, phoneNumber VARCHAR);");
            
            db.execSQL("INSERT INTO PhoneBook (name , phoneNumber) VALUES ('" + name + "','" + phoneNumber + "');");
            db.setTransactionSuccessful();
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		
		finally
		{
			db.endTransaction();
		}
		
		return true;
		
	}
	
	public void deleteDB(Context context)
	{
		SQLiteDatabase db = context.openOrCreateDatabase(dbName, 0, null);
		
		db.delete("PhoneBook", null, null);
		
	}
	
	public String readDB(Context context)
	{
		
		SQLiteDatabase db = context.openOrCreateDatabase(dbName, 0, null);
		Cursor dbCursor = null;
		StringBuilder builder = new StringBuilder();
		
		if(!db.isOpen())
			return null;
		
		db.beginTransaction();
		try{
			dbCursor = db.query( "PhoneBook", null, null, null, null, null, null); 
			
            int nameCol = dbCursor.getColumnIndex("name");
            int numberCol = dbCursor.getColumnIndex("phoneNumber");
            
            if (dbCursor != null) {
            	dbCursor.moveToFirst();
            	 //make sure that there's something there
                 if (dbCursor.getCount() != 0) {
                      
                	 int i = 0;
                      /* Loop through all Results */
                      do {
                           i++;
                           /* Retrieve the values of the Entry
                            * the Cursor is pointing to. */
                           String name = dbCursor.getString(nameCol);
                           String number    = dbCursor.getString(numberCol);
                           
                           String ageColumName = dbCursor.getColumnName(numberCol);
                           
                           builder.append(name + "\t" + number + "\n");
                           
                      } while (dbCursor.moveToNext());
                 }
            }
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		
		finally
		{
			db.endTransaction();
		}
		
		return builder.toString();
		
	}
}
	

