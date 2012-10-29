
public class SelectionSort {

	public SelectionSort() {
		
	}
	
	/**
	 * This is the improved version of Selection Sort
	 * @param input
	 * @return
	 */
	public long sort(int[] input) {
		int[] output = input.clone();
		long basicOps = 0;
		
		for (int i = 0; i < output.length - 1; ++i) {
			int min = i;
			
			for (int j = i + 1; j < output.length; ++j) {
				if (output[j] < output[min]) {
					min = j;
					basicOps++;
				}
			}
			if (i != min) {
				int tmpSwap = output[i];
				output[i] = output[min];
				output[min] = tmpSwap;
				basicOps++;
			}
		}
		
		return basicOps;
	}
}
