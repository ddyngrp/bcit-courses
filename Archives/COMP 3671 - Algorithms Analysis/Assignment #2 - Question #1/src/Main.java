/**
 * Assignment #2 - Question #1
 * @author Steffen L. Norgren - A00683006
 *
 */

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Mergesort ms = new Mergesort();
		Quicksort qs = new Quicksort();
		Heapsort hs = new Heapsort();
		
		ms.runTests(100); // Run the Mergesort tests
		System.out.println();
		qs.runTests(100); // Run the Quicksort tests		
		System.out.println();
		hs.runTests(100); // Run the Heapsort tests		
	}
}
