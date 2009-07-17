
public class BubbleSort {
	
	public BubbleSort() {
		
	}
	
	public long sort(int[] input) {
		int[] output = input.clone();
		long basicOps = 0;
		
		for (int i = 0; i <= output.length - 2; ++i) {
			for (int j = 0; j <= output.length - 2 - i; ++j) {
				if (output[j + 1] < output[j]) {
					int tmpSwap = output[j];
					output[j] = output[j + 1];
					output[j + 1] = tmpSwap;
					basicOps++;
				}
			}
		}
		
		return basicOps;
	}
	
}
