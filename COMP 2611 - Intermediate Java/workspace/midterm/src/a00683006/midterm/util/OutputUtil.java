/**
 * Project: A00683006
 * File: OutputUtil.java
 * Date: 19-Oct-07
 * Time: 7:22:57 PM
 */
package a00683006.midterm.util;

import java.util.Collection;
import a00683006.midterm.data.*;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class OutputUtil {
	
	public static void print(Object[] array) {
		for (Object o : array) {
			System.out.println(o);
		}
	}
	
	public static void print(Collection<Student> collection) {
		for (Student o : collection) {
			System.out.println(o);
		}
	}
	
}
