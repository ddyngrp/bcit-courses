/**
 * 
 */
package a00123456.util;

/**
 * @author scirka
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
