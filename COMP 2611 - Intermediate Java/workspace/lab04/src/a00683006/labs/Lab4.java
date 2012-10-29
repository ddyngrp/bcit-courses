/**
 * Project: lab04
 * File: Lab4.java
 * Date: 8-Oct-07
 * Time: 8:40:57 PM
 */

package a00683006.labs;

import a00683006.util.ReadFile;
import a00683006.util.CollectionUtil;
import a00683006.data.DataException;
import a00683006.data.Guest;
import java.util.ArrayList;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class Lab4 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		new Lab4().test();
	}

	private void test() {
		// read the contents of a non-existent file into a new ArrayList
		ArrayList<String> scoreFile = new ReadFile().textFile("scores.txt");
		// read the contents of the file into a new ArrayList
		ArrayList<String> guestFile = new ReadFile().textFile("guests.txt");
		// ArrayList for the guest data
		ArrayList<Guest> guestList = new ArrayList<Guest>();
		
		for (String guest : guestFile) {
			System.out.println("Reading: " + guest);
			
			try {
				Guest tempGuest = new Guest(guest);
				guestList.add(tempGuest);
			}
			catch (DataException ex) {
				System.out.println(ex);
			}
		}
		
		System.out.println("=== Guests ===");
		CollectionUtil.print(guestList);
	}
}