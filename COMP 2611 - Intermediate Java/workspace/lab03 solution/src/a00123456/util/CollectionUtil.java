package a00123456.util;

import java.util.Collection;

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
	
}
