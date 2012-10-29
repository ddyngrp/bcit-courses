import java.util.*;

public class VectorExample {
	
	public static void main(String[] args) {
		Vector<Integer> v = new Vector<Integer>();
		for (int i = 0; i < 20; i++) {
			v.addElement(i);
		}

		System.out.println("Vector in original order:");
		for (int i = 0; i < v.size(); i++) {
			System.out.print(v.get(i) + " ");
		}

		System.out.println("\nVector in reverse order:");
		for (int i = v.size(); i > 0;) {
			i--;
			System.out.print(v.get(i) + " ");
		}
		
		System.out.println("\nVector as a string:");
		System.out.println(v);
	}
}
