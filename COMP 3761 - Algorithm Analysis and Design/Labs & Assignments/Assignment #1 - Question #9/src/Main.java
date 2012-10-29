/**
 * Assignment #1 - Question #9
 * @author Steffen L. Norgren - A00683006
 *
 */

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		String ref = "CABAAXBYA";
		
		System.out.println("Brute Search Found " + BruteSubString(ref) + " substrings.");
		System.out.println("Linear Search Found " + LinearSubString(ref) + " substrings.");
	}
	
	private static int BruteSubString(String ref) {
		int subStrCount = 0;
		
		for (int i = 0; i < ref.length() - 1; ++i) {
			if (ref.charAt(i) == 'A') {
				for (int j = i + 1; j < ref.length(); ++j) {
					if (ref.charAt(j) == 'B') {
						subStrCount++;
					}
				}
			}
		}
		
		return subStrCount;
	}
	
	private static int LinearSubString(String ref) {
		int subStrCount = 0;
		int aCount = 0;
		
		for (int i = 0; i < ref.length(); ++i) {
			if (ref.charAt(i) == 'A') {
				aCount++;
			}
			else if (ref.charAt(i) == 'B') {
				subStrCount += aCount;
			}
		}
		
		return subStrCount;
	}
}