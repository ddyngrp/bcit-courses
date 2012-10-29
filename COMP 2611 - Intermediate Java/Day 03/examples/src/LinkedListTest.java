import java.util.*;

/**
 * This program demonstrates operations on linked lists.
 */
public class LinkedListTest {
	public static void main(String[] args) {
		List<String> a = new LinkedList<String>();
		a.add("Angela");
		a.add("Carl");
		a.add("Erica");
		System.out.println("List \"a\"");
		System.out.println(a);

		List<String> b = new LinkedList<String>();
		b.add("Bob");
		b.add("Doug");
		b.add("Frances");
		b.add("Gloria");
		System.out.println("List \"b\"");
		System.out.println(b);

		// merge the words from b into a
		ListIterator<String> aIter = a.listIterator();
		Iterator<String> bIter = b.iterator();

		while (bIter.hasNext()) {
			if (aIter.hasNext()) {
				aIter.next();
			}
			aIter.add(bIter.next());
		}

		System.out.println("Merged lists");
		System.out.println(a);

		// remove every second name from b
		bIter = b.iterator();
		while (bIter.hasNext()) {
			bIter.next(); // skip one element
			if (bIter.hasNext()) {
				bIter.next(); // skip next element
				bIter.remove(); // remove that element
			}
		}

		System.out.println("Every second name removed from \"b\"");
		System.out.println(b);

		// bulk operation: remove all words in b from a
		System.out.println("Rmove all \"b\" names from \"a\"");
		a.removeAll(b);

		System.out.println(a);
	}
}
