import java.util.*;

/**
 * Project: work3
 * File: HashSetExample3.java
 * Date: 23/09/2007
 * Time: 5:58:53 PM
 */

public class HashSetExample3 {
	public static void main(String[] args) {
		new HashSetExample3();
	}
	
	private HashSetExample3() {
		HashSet set = new HashSet();
		System.out.println(set.add(new TestObject("This")) ? "\"This\" added" : "\"This\" rejected");
		System.out.println(set.add(new TestObject("is")) ? "\"is\" added" : "\"is\" rejected");
		System.out.println(set.add(new TestObject("is")) ? "\"is\" added" : "\"is\" rejected");
		System.out.println(set.add(new TestObject("a")) ? "\"a\" added" : "\"a\" rejected");
		System.out.println(set.add(new TestObject("a")) ? "\"a\" added" : "\"a\" rejected");
		System.out.println(set.add(new TestObject("test")) ? "\"test\" added" : "\"test\" rejected");
	
		CollectionUtil.display(set);
	}
	
	public class TestObject {
		String data;
		
		TestObject(String s) {
			data = s;
		}

		@Override
	    public int hashCode() {
			return 1;
		}
		
		@Override
		public String toString() {
			return data;
		}
	}

}
