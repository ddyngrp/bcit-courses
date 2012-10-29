import java.util.*;

public class Lab3 {
	private Stack<Integer> pancakes;	// stack for the pancakes
	private Stack<Integer> pancakeFlip;	// temporary queue to enable flipping
	private String flipPoints = "";		// temporary string to list flip points
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		new Lab3();
	}
	
	public Lab3() {
		pancakes = new Stack<Integer>();
		pancakeFlip = new Stack<Integer>();
		
		// read the returned ArrayList and process each line
		for (String pancake : new ReadFile().textFile("pancakes.txt")) {
			StringTokenizer st=new StringTokenizer(pancake, " ");
			while (st.hasMoreTokens()) {
				pancakes.push(Integer.parseInt(st.nextToken()));
			}
			printStack();		// print the resulting stack
			findFlipPoint();	// calculate flip points
			System.out.println(flipPoints); // print the list of flips
			pancakes.clear();	// clear the stack
			flipPoints = "";	// clear the list of flip points
		}
	}
	
	public void findFlipPoint() {
		int stackHeight = pancakes.size();
		int maxSize = 0;
		int ordinal = 0;
		
		while (ordinal < stackHeight) {
			for (int i = 0; i < stackHeight; i++) {
				if (pancakes.get(i) > maxSize) {
					maxSize = pancakes.get(i);
					ordinal++;
				}
			}
			flip(ordinal);
			maxSize = 0; // reset max size
		}
	}
	
	public void flip(int ordinal) {
		if (ordinal != pancakes.size()) {
			while (pancakes.size() != (ordinal-1)) {
				// remove from stack and add to queue
				pancakeFlip.add(pancakes.remove(ordinal-1));
			}
			
			while (!pancakeFlip.isEmpty()) {
				// remove from queue and add to stack
				pancakes.add(pancakeFlip.remove(pancakeFlip.size()-1));
			}
		}
		else {
			ordinal = 0; // we do nothing, so there is no flip
		}
		flipPoints = flipPoints + (ordinal) + " ";
	}
	
	public void printStack() {
		for (Integer diameter: pancakes) {
			System.out.print(diameter + " ");
		}
		System.out.println();
	}
}