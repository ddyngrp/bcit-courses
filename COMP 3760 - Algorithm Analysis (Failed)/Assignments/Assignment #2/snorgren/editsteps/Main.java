package editsteps;

import java.util.Iterator;
import java.util.Map;

/**
 * This is the program's main entry point. It handles passing
 * command line arguments to a file reader and verifying that
 * the command-line input syntax is correct.
 * 
 * @author Steffen L. Norgren, A00683006
 * @data 2008-11-22
 *
 */
public class Main {

	/**
	 * This main method verifies the correctness of input via the
	 * command line and passes the arguments to the ReadFile class
	 * and the results to the ParseData class.
	 * 
	 * @param args file name to be input.
	 */
	public static void main(String[] args) {
		if (args.length == 1) {
			ParseData pd = new ParseData(new ReadFile().textFile(args[0]));
			//System.out.print(pd.toString()); // testing purposes
			
			// Create Adjacency lists for all of our word lists and then traverse them
			for (int i = 1; i <= pd.getWordMap().size(); ++i) {
				AdjacencyList lst = new AdjacencyList(pd.getWordMap().get(i));
				
				// Cycle through our transformations for this test case
				Iterator<Map.Entry<String, String>> tfIT = pd.getTransformMap().get(i).entrySet().iterator();
				System.out.println("// Test Case " + i);
				//lst.toString();
				while (tfIT.hasNext()) {
					// Process the transformation
					Map.Entry<String, String> transform = tfIT.next();
					String start = transform.getKey();
					String end = transform.getValue();
					int steps = lst.ShortestTraversal(start.toLowerCase(), end.toLowerCase());
					
					if (steps == -1) {
						System.out.println(start + " " + end + " (not possible)");
					}
					else if (steps == 0) {
						System.out.println(start + " " + end + " (same starting and ending word)");
					}
					else {
						System.out.println(start + " " + end + " " + steps);
					}
				}
				System.out.println("ladder: " + lst.Ladder());
			}
			
		} else if (args.length > 1) {
			System.err.println("ERROR: Too many arguments.");
			help();
		} else {
			help();
		}
	}

	/**
	 * This method prints out the correct command usage in event that incorrect
	 * parameters were sent via the command line.
	 */
	private static void help() {
		String helpString = "  Usage: java editsteps/Main [argument]\n"
						  + "  Where [argument] is the path to the file "
						  + "being input.";

		System.err.println(helpString);
	}
}