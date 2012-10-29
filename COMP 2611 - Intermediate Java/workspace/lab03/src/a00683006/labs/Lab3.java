/**
 * Project: lab02
 * File: Lab2.java
 * Date: 24-Sep-07
 * Time: 12:50:57 AM
 */
package a00683006.labs;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Collections;
import java.util.Comparator;
import java.util.Set;
import java.util.TreeSet;

import a00683006.data.Address;
import a00683006.data.Guest;
import a00683006.util.CollectionUtil;;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class Lab3 {
	
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
		new Lab3().test();
	}
	
	public void test() {
		// create a new ArrayList of type Guest
		List<Guest> guestList = new ArrayList<Guest>();
		
		// populate the Arraylist
		for (int i = 0; i < GUEST_DATA.length; i++) {
			Guest guest = new Guest(GUEST_DATA[i]);
			Address address = new Address(ADDRESS_DATA[i]);
			guest.setAddress(address);
			guestList.add(guest);
		}
		
		System.out.println("Original list:");
		CollectionUtil.print(guestList);

		System.out.println("List sorted by last name:");
		CompareByLastName compareObject = new CompareByLastName();
		Collections.sort(guestList, compareObject);
		CollectionUtil.print(guestList);

		System.out.println("Set automatically sorted by City:");
		TreeSet<Guest> guestSet = new TreeSet<Guest>(guestList);
		System.out.println(guestSet.add(guestSet.first()) ? "The guest list is not a set." :
															"The guest list is a set.");
		CollectionUtil.print(guestSet);
		
		System.out.println("The map:");
		HashMap<String, Guest> guestMap = new HashMap<String, Guest>();
		// populate the HashMap from the guestList
		for (Guest guest : guestList) {
			guestMap.put(guest.getAddress().getPostalCode(), guest);
		}
		// convert to a collection so CollectionUtil is happy
		Collection colectGuestMap = guestMap.entrySet();
		CollectionUtil.print(colectGuestMap);
	}
	
	// sort by last name
	private class CompareByLastName implements Comparator<Guest> {
		public int compare(Guest g1, Guest g2) {
			// our sorting criteria is the last name
			return g1.getLastName().compareTo(g2.getLastName());
		}
	}
}