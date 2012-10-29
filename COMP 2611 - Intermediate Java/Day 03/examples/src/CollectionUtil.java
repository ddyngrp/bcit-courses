import java.util.Collection;
import java.util.Iterator;

public class CollectionUtil {

	// note that we don't care what the collection is
	static void display(Collection collection) {
		System.out.println("The size is: " + collection.size());
		Iterator iterator = collection.iterator();
		while (iterator.hasNext()) {
			Object o = iterator.next();
			System.out.println(o);
		}
	}

	static void display(Object[] items) {
		for (int i = 0; i < items.length; i++) {
			System.out.println(items[i]);
		}
	}

	public static String print(Object[] items, String separator) {
		StringBuffer buffer = new StringBuffer();
		for (int i = 0; i < items.length; i++) {
			if (i > 0) {
				buffer.append(separator);
			}
			buffer.append(items[i]);
		}
		
		return buffer.toString();
	}
}
