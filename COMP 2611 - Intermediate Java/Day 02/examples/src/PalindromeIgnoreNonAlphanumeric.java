import javax.swing.JOptionPane;

public class PalindromeIgnoreNonAlphanumeric {
	/** Main method */
	public static void main(String[] args) {
		// Prompt the user to enter a string
		String s = JOptionPane.showInputDialog("Enter a string:");

		// Declare and initialize output string
		String output = "Ignoring non-alphanumeric characters, \nis " + s
				+ " a palindrome? " + isPalindrome(s);

		// Display the result
		JOptionPane.showMessageDialog(null, output);
	}

	/** Return true if a string is a palindrome */
	public static boolean isPalindrome(String s) {
		// Create a new string by eliminating non-alphanumeric chars
		String s1 = filter(s);

		// Create a new string that is the reversal of s1
		String s2 = reverse(s1);

		// Compare if the reversal is the same as the original string
		return s2.equals(s1);
	}

	/** Create a new string by eliminating non-alphanumeric chars */
	public static String filter(String s) {
		// Create a string buffer
		StringBuilder strBuf = new StringBuilder();

		// Examine each char in the string to skip alphanumeric char
		for (int i = 0; i < s.length(); i++) {
			if (Character.isLetterOrDigit(s.charAt(i))) {
				strBuf.append(s.charAt(i));
			}
		}

		// Return a new filtered string
		return strBuf.toString();
	}

	/** Create a new string by reversing a specified string */
	public static String reverse(String s) {
		StringBuilder strBuf = new StringBuilder(s);
		strBuf.reverse(); // Use the reverse method for StringBuilder object
		return strBuf.toString();
	}
}
