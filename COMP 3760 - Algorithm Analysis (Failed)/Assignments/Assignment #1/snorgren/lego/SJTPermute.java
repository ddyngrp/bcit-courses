package lego;

/**
 * This class implements the Steinhaus-Johnson-Trotter algorithm 
 * which generates permutations by transposing elements in a
 * given list. It will then return the results using a 2-dimensional
 * array.
 *   
 * @author Steffen L. Norgren, A00683006
 * @data 2008-10-12
 *
 */
public class SJTPermute {
    private int[][] finalPermutations;	// the array of permutations we'll return
    private int iteration = 0;			// current iteration

	/**
	 * This method takes an input of N to generate a list of all possible
	 * permutations for a given list of N elements. For example, if N=3
	 * we'll generate all permutations for {0,1,2}.
	 * 
	 * @param N the number of permutations we'll create.
	 * @return int[][] a 2-dimensional array of N permutations
	 */	
	public int[][] permute(int N) {
    	int[] permutation = new int[N];			// permutation
        int[] invPermutation = new int[N];		// inverse permutation
        int[] direction = new int[N];			// direction = +1 or -1
        
        finalPermutations = new int[new Factorial().factorial(N)][N];
        
        // setup the initial conditions
        for (int i = 0; i < N; i++) {
        	direction[i] = -1;
            permutation[i] = i;
            invPermutation[i] = i;
        }
        permute(0, permutation, invPermutation, direction);
        
        return finalPermutations;
	}

	
	/**
	 * This is a recursive method that iterates through all the permutations
	 * for a given list of n elements. 
	 * 
	 * @param N the number of permutations we'll create.
	 * @param int[] the current permutation
	 * @param int[] inverse of the current permutation
	 * @param int[] current directions for the current permutation
	 */	
	private void permute(int n, int[] permutation, int[] invPermuation, int[] direction) {

		// base case - print out permutation
		if (n >= permutation.length) {
			for (int i = 0; i < permutation.length; i++) {
				// add results to our return array
				finalPermutations[iteration][i] = permutation[i];
			}
			iteration++; // increment the current iteration
			return;
		}

		// set up the initial permutation
		permute(n + 1, permutation, invPermuation, direction);
		
		// Swap the elements
		for (int i = 0; i <= n - 1; i++) {
			// swap elements
			int z = permutation[invPermuation[n] + direction[n]];
			permutation[invPermuation[n]] = z;
			permutation[invPermuation[n] + direction[n]] = n;
			invPermuation[z] = invPermuation[n];
			invPermuation[n] = invPermuation[n] + direction[n];

			// continue the recursive calls until we've finished all permutations.
			permute(n + 1, permutation, invPermuation, direction); 
		}
		direction[n] = -direction[n];	// change direction
    }
}