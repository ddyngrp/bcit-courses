package lego;

/**
 * Main entry point for the program. It takes input
 * from the command line and passes that input to the
 * LegoSort class.
 *   
 * @author Steffen L. Norgren, A00683006
 * @data 2008-10-12
 *
 */
public class Main {

	/**
	 * This main method verifies the correctness of input via the
	 * command line and passes the arguments to the ReadFile class
	 * and the LegoSort class.
	 * 
	 * @param String[] of arguments passed via the command line.
	 */
	public static void main(String[] args) {
		if (args.length == 1) {
			new LegoSort(new ReadFile().textFile(args[0]));
		}
		else if (args.length > 1) {
			System.out.println("ERROR: Too many arguments.");
			help();
		}
		else {
			help();
		}
	}
	
	/**
	 * This method prints out the correct command usage in event
	 * that incorrect parameters were sent via the command line.
	 */
	private static void help() {
		String helpString =
				"  Usage: java lego/Main [argument]\n" +
				"  Where [argument] is the path to the file " +
				"being input.";
		
		System.out.println(helpString);
	}
}
