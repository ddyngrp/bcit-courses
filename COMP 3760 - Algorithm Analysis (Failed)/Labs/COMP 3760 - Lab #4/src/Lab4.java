import java.io.*;
import java.util.*;

public class Lab4 {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		new Lab4();
	}
	
	public Lab4() {
		//q1();
		//q2();
		//q3();
		q4();
	}
	
	// Question 1 - This will output all the elements input, regardless of size
	// because despite creating it with 10 elements, the HashSet will automatically
	// grow beyond that. The creation of 10 only tells Java that it should be
	// ready to deal with an input of 10 elements.
	public void q1() {
		HashSet<String> q1 = new HashSet<String>(10);
		int i = 1;
		
		// read the returned ArrayList and process each line
		for (String s : new ReadFile().textFile("q1input.txt")) {
			q1.add(s);
		}
		
		Iterator<String> it = q1.iterator();
		while (it.hasNext()) {
			System.out.println("String " + i++ + " : " + it.next());
		}
	}

	// Question 2 - The TreeSet is automatically sorted and duplicates removed.
	public void q2() {
		TreeSet<String> q2 = new TreeSet<String>();

		int i = 1;
		
		// read the returned ArrayList and process each line
		for (String s : new ReadFile().textFile("q1input.txt")) {
			q2.add(s);
		}
		
		Iterator<String> it = q2.iterator();
		while (it.hasNext()) {
			Object o1 = it.next();
			System.out.println("String " + i++ + ": " + o1);
		}
	}
	
	// Question 3 - the efficiency class should be ~= O(n)
	public void q3() {
		LinkedList<String> q3 = new LinkedList<String>();
		HashSet<String> q3dup = new HashSet<String>();
		boolean duplicate = false;
		
		for (String s : new ReadFile().textFile("q1input.txt")) {
			q3.add(s);
		}
		
		Iterator<String> it = q3.iterator();
		while (it.hasNext()) {
			String s1 = it.next();
			if (q3dup.add(s1) == false && !duplicate) {
				duplicate = true;
			}
			System.out.println(s1);
		}
		if (duplicate) {
			System.out.println("LIST NOT DISTINCT");
		}
		else {
			System.out.println("LIST IS DISTINCT");
		}
	}
	
	public void q4() {
		TreeMap<String, Integer> q4tm = new TreeMap<String, Integer>();
		
		// read the returned ArrayList and process each line
		for (String q4 : new ReadFile().textFile("lyrics.txt")) {
			StringTokenizer st=new StringTokenizer(q4, " ");
			while (st.hasMoreTokens()) {
				String s1 = st.nextToken();
				if (!q4tm.containsKey(s1)) {
					q4tm.put(s1.toLowerCase(), 1);
				}
				else {
					q4tm.put(s1, q4tm.get(s1) + 1);
				}
			}
		}

		Set keys = q4tm.keySet();
		Iterator it = keys.iterator();
		while (it.hasNext()) {
			String s = (String)it.next();
			System.out.println(s + " - " + q4tm.get(s));
		}
		
	}
}