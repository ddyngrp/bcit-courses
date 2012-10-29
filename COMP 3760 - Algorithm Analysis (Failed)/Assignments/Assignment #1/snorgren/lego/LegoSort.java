package lego;

import java.util.*;

/**
 * This class will calculate how to optimally sort
 * m types of Lego among n storage containers.
 *   
 * @author Steffen L. Norgren, A00683006
 * @data 2008-10-12
 *
 */
public class LegoSort {
	private int[][] permutations;	// numerical list of permutations for the current block of data.
	private char[] legoBins;		// array of lego bins
	private int[][] legoLocations;	// location of lego pieces by bin
	private int sumOfLego;			// total sum of lego
	
	/**
	 * This method parses the data we read in via the command line
	 * and sets up the initial conditions for sorting the Lego.
	 * 
	 * @param inputData representing the file we read in via the
	 * command line.
	 */
	public LegoSort(ArrayList<String> inputData) {
		int elements;
		
		for (int i = 0; i < inputData.size(); ) {
			elements = Integer.parseInt(inputData.get(i).trim());
			ManageInput(inputData, i + 1, elements + i + 1);
			FindSortMoves();
			i += elements + 2; // go to the next block
		}
	}
	
	/**
	 * This method reads a "block" from our input ArrayList. The block
	 * of data is then parsed such that we can begin the sorting algorithm.
	 * 
	 * @param inputData representing the file we read in via the
	 * command line.
	 * @param startLine for the starting line for the block to deal with
	 * @param endLine for the number of line elements we'll be dealing with 
	 */
	private void ManageInput(ArrayList<String> inputData, int startLine, int endLine) {
		// get list of bins
		StringTokenizer st = new StringTokenizer(inputData.get(startLine));
		
		int tokens = st.countTokens();				// number of tokens for the data bock
		legoBins = new char[tokens];				// initialize lego bin array
		legoLocations = new int[tokens][tokens];	// initialize lego locations
		sumOfLego = 0;								// set the lego sum to 0 for new block
		
		for (int i = 0; i < tokens; i++) {
			char c = st.nextToken().charAt(0); // convert the string element to char
			legoBins[i] = c;
		}
		
		// create an array of possible permutations
		permutations = new SJTPermute().permute(tokens);
		
		// loop through the numerical block of data and insert it into the
		// legoLocation array.
		for (int i = startLine + 1; i <= endLine; i++) {
			StringTokenizer st2 = new StringTokenizer(inputData.get(i));
			tokens = st2.countTokens();
			for (int k = 0; k < tokens; k++) {
				int currentToken = Integer.parseInt(st2.nextToken());
				legoLocations[i - startLine - 1][k] = currentToken;
				sumOfLego += currentToken;
			}
		}
	}
	
	/**
	 * This method populates a TreeMap with the number of moves used to sort
	 * the lego bins. The key for this TreeMap is the number of moves, while
	 * the data for each key is the row of the permutations array that was used
	 * to generate the moves. Since this is a TreeMap, the first entry will
	 * always be the least number of moves needed to sort the lego bins.
	 */
	private void FindSortMoves() {
		TreeMap<Integer, Integer> sumMap = new TreeMap<Integer, Integer>();
		int sumOfMoves;		// total sum of moves needed to sort bins
		int permLine = 0;	// line of permutations that resulted in the lest moves
		
		// populate a TreeMap with all possible ways to sort lego
		for (int i = 0; i < permutations.length; i++) {
			sumOfMoves = 0;
			for (int k = 0; k < permutations[0].length; k++) {
				//System.out.print(permutations[i][k]);
				sumOfMoves += legoLocations[k][permutations[i][k]];
			}
			
			permLine = i;
			sumOfMoves = sumOfLego - sumOfMoves;
			
			// exclude duplicates
			if (sumMap.get(sumOfMoves) == null) {
				sumMap.put(sumOfMoves, permLine);
			}
		}
		
		PrintLeastSort(sumMap);
	}
	
	/**
	 * This method prints out the results of our sorted bins. It grabs
	 * the data first entry in the TreeMap, which corresponds to a row
	 * in the permutations array. This is used to print out the order
	 * of the bins. The key is then printed out, as that is the number
	 * of moves used to sort the lego.
	 */
	private void PrintLeastSort(TreeMap<Integer, Integer> sumMap) {
		Iterator<Integer> it = sumMap.keySet().iterator();
		int firstKey = it.next(); // get the first key in the TreeMap
		
		// print out the order of the bins
		for (int i = 0; i < permutations[sumMap.get(firstKey)].length; i++) {
			System.out.print(legoBins[permutations[sumMap.get(firstKey)][i]]);
		}
		
		// print the number of moves
		System.out.println(" " + firstKey);
	}
}