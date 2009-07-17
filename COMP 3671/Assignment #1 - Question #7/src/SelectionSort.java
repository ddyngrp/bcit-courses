
public class SelectionSort {

	public SelectionSort() {
		
	}
	
	public long sort(int[] input) {
		int[] output = input.clone();
		long basicOps = 0;
		
		for (int i = 0; i <= output.length - 2; ++i) {
			int min = i;
			
			for (int j = i + 1; j <= output.length - 1; ++j) {
				if (output[j] < output[min]) {
					min = j;
					basicOps++;
				}
			}
			basicOps++;
			int tmpSwap = output[i];
			output[i] = output[min];
			output[min] = tmpSwap;
		}
		
		return basicOps;
	}
}
