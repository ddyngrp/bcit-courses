package a00123456.data;

import java.util.Comparator;
import java.util.GregorianCalendar;

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
			return emailAddress0.compareToIgnoreCase(emailAddress0);
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
