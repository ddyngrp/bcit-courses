/**
 * Project: lab02
 * File: Lab2.java
 * Date: 24-Sep-07
 * Time: 12:50:57 AM
 */
package a00683006.labs;

import a00683006.data.Address;
import a00683006.data.Guest;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class Lab2 {
	
	private final String[][] GUEST_DATA = {
				{ "Lee", "Brenda", "(604) 636-1000", "b.lee@bcit.ca" },
				{ "Sullivan", "Sam", "604-873-7011", "Sam777@hotmail.com" },
				{ "Johansen", "Lars", "(604) 636-1000", "Lars147@gmail.com" }};
	private final String[][] ADDRESS_DATA = {
				{ "3700 Willingdon Avenue", "Burnaby", "British Columbia", "V5G 3H2", "Canada" },
				{ "453 West 12th Avenue", "Vancouver", "BC", "V5Y 1V4", "Canada" },
				{ "1000 Lougheed Highway", "Coquitlam", "British Columbia", "V3K 3T5", "" }};
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		new Lab2().test();
	}
	
	public void test() {
		// create a new Guest array with the same length as the input data.
		Guest[] guestArray = new Guest[GUEST_DATA.length];
		
		for (int i = 0; i < GUEST_DATA.length; i++) {
			guestArray[i] = new Guest(GUEST_DATA[i], new Address(ADDRESS_DATA[i]));
		}
		listGuests(guestArray);
	}
	
	public void listGuests(Guest[] guestArray) {
		for (int i = 0; i < guestArray.length; i++) {
			System.out.println(guestArray[i]);
		}
	}
}