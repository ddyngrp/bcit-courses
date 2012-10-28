
public class BubbleSort {
	
	public BubbleSort() {
		
	}
	
	/**
	 * This is the improved version of Bubble Sort
	 * @param input
	 * @return
	 */
	public long sort(int[] input) {
		int[] output = input.clone();
		long basicOps = 0;
		boolean swapped;
		
		do {
			swapped = false;
			for (int i = 0; i < output.length - 1; ++i) {
				if (output[i + 1] < output[i]) {
					int tmpSwap = output[i];
					output[i] = output[i + 1];
					output[i + 1] = tmpSwap;
					swapped = true;
					basicOps++;
				}
			}			
		} while (swapped);
		
		return basicOps;
	}
	
}
