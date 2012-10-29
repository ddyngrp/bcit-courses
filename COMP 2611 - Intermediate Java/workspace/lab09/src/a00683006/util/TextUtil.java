/**
 * Project: lab09
 * File: TextUtil.java
 * Date: 13-Nov-07
 * Time: 12:46:51 AM
 */
package a00683006.util;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class TextUtil {
	
	public static String addQuotesIfEmbeddedWhitespace(String s) {
		if (s.indexOf(' ') != -1) {
			return String.format("\"%s\"", s);
		}
		
		return s;
	}

	public static String removeQuotes(String s) {
		if (s == null || s.trim().length() == 0) {
			return s;
		}
		
		s = s.trim();
		if (s.startsWith("\"") && s.endsWith("\"")) {
			return s.substring(1, s.length() - 1);
		}
		
		return s;
	}

}
