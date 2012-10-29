/**
 * Project: lab03
 * File: CollectionUtil.java
 * Date: 1-Oct-07
 * Time: 2:15:36 AM
 */
package a00683006.util;

import java.util.Collection;
import java.util.Iterator;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class CollectionUtil {

	public static void print(Object[] array) {
		for (int i = 0; i < array.length; i++) {
			System.out.println(array[i]);
		}
	}
	
	public static void print(Collection collection) {
		Iterator iterator = collection.iterator();
		while (iterator.hasNext()) {
			Object o = iterator.next();
			System.out.println(o);
		}
	}
}