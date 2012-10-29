/**
 * Project: assignment01
 * File: CollectionUtil.java
 * Date: 1-Oct-07
 * Time: 7:38:17 PM
 */
package a00683006.bedz.util;

import java.util.Collection;

/**
 * This is a utility class that will return a string representation
 * of any array or collection.
 * @author Steffen L. Norgren, A00683006
 *
 */
public class CollectionUtil {
	
	/**
	 * Return the contents of an array as a string.
	 * @param array
	 * @return string representation of an array.
	 */
	public static String getString(Object[] array) {
		String returnString = "";
		
		for (Object o : array) {
			returnString += o.toString() + "\n";
		}
		return returnString;
	}
	
	/**
	 * Return the contents of a collection as a string.
	 * @param array
	 * @return string representation of a collection.
	 */
	public static String getString(Collection collection) {
		String returnString = "";

		for (Object o : collection) {
			returnString += o.toString() + "\n";
		}
		return returnString;
	}
}
