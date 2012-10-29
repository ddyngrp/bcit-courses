/**
 * Project: Lab3
 * File: Lab3.java
 * Date: Sep 24, 2007
 * Time: 9:09:14 PM
 */

package a00123456.labs;

import java.util.*;

import a00123456.data.Address;
import a00123456.data.Guest;
import a00123456.data.GuestSorter;
import a00123456.util.CollectionUtil;

/**
 * @author Fred Fish, A00123456
 * 
 */
public class Lab3 {

	// public Address(String street, String city, String province, String
	// postalCode, String country) {
	private final String[][] ADDRESS_DATA = {
			{ "3700 Willingdon Avenue", "Burnaby", "British Columbia",
					"V5G 3H2", "Canada" },
			{ "453 West 12th Avenue", "Vancouver", "BC", "V5Y 1V4", "Canada" },
			{ "1000 Lougheed Highway", "Coquitlam", "British Columbia",
					"V3K 3T5", "" } };

	// public Guest(String lastName, String firstName, String phoneNumber,
	// String emailAddress) {
	private final String[][] GUEST_DATA = {
			{ "Lee", "Brenda", "(604) 636-1000", "b.lee@bcit.ca" },
			{ "Sullivan", "Sam", "604-873-7011", "Sam777@hotmail.com" },
			{ "Johansen", "Lars", "(604) 636-1000", "Lars147@gmail.com" } };

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		new Lab3().test();
	}

	private void test() {
		ArrayList<Guest> guests = new ArrayList<Guest>();

		for (int i = 0; i < GUEST_DATA.length; i++) {
			Guest guest = new Guest(GUEST_DATA[i]);
			Address address = new Address(ADDRESS_DATA[i]);
			guest.setAddress(address);
			guests.add(guest);
		}

		// Original guest list:
		System.out.println("Original list:");
		CollectionUtil.print(guests);
		
		// Guest list sorted by last name:
		System.out.println("List sorted by last name:");
		GuestSorter.ByLastName byLastNameComparator = new GuestSorter.ByLastName();
		Collections.sort(guests, byLastNameComparator);
		CollectionUtil.print(guests);
		
		// Determine if the guest list is a set:
		SortedSet<Guest> set = new TreeSet<Guest>(new GuestSorter.ByCity());
		set.addAll(guests);
		if (set.size() == guests.size()) {
			System.out.println("The guest list is a set.");
		} else {
			System.out.println("The guest list is not a set.");
		}
		
		// Display the set
		System.out.println("Set automatically sorted by City:");
		CollectionUtil.print(set);
		
		// Create a map with the postal code as the key
		HashMap<String, Guest> map = new HashMap<String, Guest>();
		for (Guest guest : guests) {
			map.put(guest.getAddress().getPostalCode(), guest);
		}
		
		// display the map
		System.out.println("The map:");
		CollectionUtil.print(map.entrySet());
	}

}