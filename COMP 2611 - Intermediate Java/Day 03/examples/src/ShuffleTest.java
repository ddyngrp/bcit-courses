import java.util.*;

/**
 * This program demonstrates the random shuffle and sort algorithms.
 */
public class ShuffleTest {
	
	public static void main(String[] args) {
		List<Integer> numbers = new ArrayList<Integer>(49);
		for (int i = 1; i <= 49; i++) {
			numbers.add(i);
		}
		Collections.shuffle(numbers);
		List<Integer> winningCombination = numbers.subList(0, 6);
		Collections.sort(winningCombination);
		System.out.println(winningCombination);
	}
}
