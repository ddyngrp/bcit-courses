/**
 @version 1.00 1999-07-07
 @author Cay Horstmann
 */

import java.util.*;

/**
 * This program sorts a set of item by comparing their descriptions.
 */
public class TreeSetTest {
	public static void main(String[] args) {
		SortedSet<Item> parts = new TreeSet<Item>();
		parts.add(new Item("Toaster", 1234));
		parts.add(new Item("Widget", 4562));
		parts.add(new Item("Modem", 9912));
		System.out.println(parts);

		SortedSet<Item> sortByDescription = new TreeSet<Item>(new Comparator<Item>() {
			public int compare(Item itemA, Item itemB) {
				String descrA = itemA.getDescription();
				String descrB = itemB.getDescription();
				return descrA.compareTo(descrB);
			}
		});

		sortByDescription.addAll(parts);
		System.out.println(sortByDescription);
	}
}

/**
 * An item with a description and a part number.
 */
class Item implements Comparable {
	/**
	 * Constructs an item.
	 * 
	 * @param aDescription
	 *            the item's description
	 * @param aPartNumber
	 *            the item's part number
	 */
	public Item(String aDescription, int aPartNumber) {
		description = aDescription;
		partNumber = aPartNumber;
	}

	/**
	 * Gets the description of this item.
	 * 
	 * @return the description
	 */
	public String getDescription() {
		return description;
	}

	public String toString() {
		return "[descripion=" + description + ", partNumber=" + partNumber
				+ "]";
	}

	public boolean equals(Object other) {
		if (getClass() == other.getClass()) {
			Item otherItem = (Item) other;
			return description.equals(otherItem.description)
					&& partNumber == otherItem.partNumber;
		} else
			return false;
	}

	public int hashCode() {
		return 13 * description.hashCode() + 17 * partNumber;
	}

	public int compareTo(Object other) {
		Item otherItem = (Item) other;
		return partNumber - otherItem.partNumber;
	}

	private String description;

	private int partNumber;
}
