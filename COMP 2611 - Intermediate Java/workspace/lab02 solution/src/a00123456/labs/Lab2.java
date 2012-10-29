/**
 * Project: Lab2
 * File: Lab2.java
 * Date: Sep 18, 2006
 * Time: 9:09:14 PM
 */

package a00123456.labs;

import java.util.Arrays;

import a00123456.data.Address;
import a00123456.data.Guest;

/**
 * @author Fred Fish, A00123456
 * 
 */
public class Lab2 {

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
		new Lab2().test();
	}

	private void test() {
		Guest[] guests = new Guest[GUEST_DATA.length];

		for (int i = 0; i < GUEST_DATA.length; i++) {
			Guest guest = new Guest(GUEST_DATA[i]);
			Address address = new Address(ADDRESS_DATA[i]);
			guest.setAddress(address);
			guests[i] = guest;
		}

		for (int i = 0; i < GUEST_DATA.length; i++) {
			System.out.println(guests[i]);
		}
	}

}