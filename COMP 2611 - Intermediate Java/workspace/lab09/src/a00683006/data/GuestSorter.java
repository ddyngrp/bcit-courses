/**
 * Project: lab09
 * File: GuestSorter.java
 * Date: 12-Nov-07
 * Time: 4:48:44 PM
 */
package a00683006.data;

import java.util.Comparator;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class GuestSorter {

	public static class ByLastName implements Comparator<Guest> {

		public int compare(Guest guest0, Guest guest1) {
			String title0 = guest0.getLastName() == null ? "" : guest0.getLastName();
			String title1 = guest1.getLastName() == null ? "" : guest1.getLastName();
			return title0.compareToIgnoreCase(title1);
		}
	}

	public static class ByEmailAddress implements Comparator<Guest> {

		public int compare(Guest guest0, Guest guest1) {
			String emailAddress0 = guest0.getEmailAddress() == null ? "" : guest0.getEmailAddress();
			String emailAddress1 = guest1.getEmailAddress() == null ? "" : guest1.getEmailAddress();
			return emailAddress0.compareToIgnoreCase(emailAddress1);
		}
	}

	public static class ByCity implements Comparator<Guest> {

		public int compare(Guest guest0, Guest guest1) {
			String city0 = guest0.getAddress().getCity();
			String city1 = guest1.getAddress().getCity();
			return city0.compareToIgnoreCase(city1);
		}
	}

}
