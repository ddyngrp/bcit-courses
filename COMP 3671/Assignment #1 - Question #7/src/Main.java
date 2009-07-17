/**
 * Assignment #1 - Question #7
 * @author Steffen L. Norgren - A00683006
 *
 */
import java.util.Calendar;
import java.util.Random;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		SelectionSort ss = new SelectionSort();
		BubbleSort bs = new BubbleSort();
		
		int runs = 25;
		int[] magnitudes = {10, 100, 500, 1000, 5000, 10000, 25000, 50000};
		
		System.out.println("--- Initiating Selection Sort with " + runs + " repetitions ---\n");
		System.out.println("Input Size, Average Operations");
		for (int i = 0; i < magnitudes.length; ++i) {
			long avgOps = 0;
			for (int j = 0; j < runs; ++j) {
				avgOps += ss.sort(MakeRandArray(magnitudes[i]));
			}
			avgOps /= runs;
			System.out.println(magnitudes[i] + ", " + avgOps);
		}
		
		System.out.println("\n --- Initiating Bubble Sort with " + runs + " repetitions ---\n");
		System.out.println("Input Size, Average Operations");
		for (int i = 0; i < magnitudes.length; ++i) {
			long avgOps = 0;
			for (int j = 0; j < runs; ++j) {
				avgOps += bs.sort(MakeRandArray(magnitudes[i]));
			}
			avgOps /= runs;
			System.out.println(magnitudes[i] + ", " + avgOps);
		}
	}
	
	private static int[] MakeRandArray(int size) {
		int[] array = new int[size];
		Calendar rightNow = Calendar.getInstance();
		Random generator = new Random(rightNow.getTimeInMillis());
		
		for (int i = 0; i < size; i++) {
			array[i] = generator.nextInt();
		}
		
		return array;
	}
}
