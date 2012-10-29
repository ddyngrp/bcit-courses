/**
 * Project: lab09
 * File: CollectionUtil.java
 * Date: 8-Oct-07
 * Time: 8:40:57 PM
 */

package a00683006.util;

import java.util.Collection;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class CollectionUtil {

	public static void print(Object[] array) {
		for (Object o : array) {
			System.out.println(o);
		}
	}
	
	public static void print(Collection collection) {
		for (Object o : collection) {
			System.out.println(o);
		}
	}
	
	public static String returnText(Object[] array) {
		String returnString = "";
		for (Object o : array) {
			returnString += o + "\n";
		}
		return returnString;
	}
	
	public static String returnText(Collection collection) {
		String returnString = "";
		for (Object o : collection) {
			returnString += o + "\n";
		}
		return returnString;
	}
}
