/**
 * Project: assignment02
 * File: Console.java
 * Date: 24-Sep-07
 * Time: 2:20:59 AM
 */
package a00683006.bedz.ui;

import java.util.Collection;

/**
 * Prints the contents of any string, array, or collection to the console.
 * @author Steffen L. Norgren, A00683006
 *
 */
public class Console {
	
	/**
	 * Prints the contents of a string to the console.
	 * @param printString
	 */
	public void print(String printString) {
		System.out.println(printString);
	}
	
	/**
	 * Prints the contents of an array to the console.
	 * @param array
	 */
	public void print(Object[] array) {
		for (Object o : array) {
			System.out.println(o.toString());
		}
	}
	
	/**
	 * Prints the contents of a collection to the console.
	 * @param collection
	 */
	public void print(Collection collection) {
		for (Object o : collection) {
			System.out.println(o.toString());
		}
	}
}