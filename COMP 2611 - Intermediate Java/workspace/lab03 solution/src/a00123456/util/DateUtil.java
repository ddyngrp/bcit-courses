/**
 * Project: Lab2
 * File: DateUtil.java
 * Date: Sep 19, 2006
 * Time: 2:38:51 PM
 */

package a00123456.util;

import java.text.DateFormat;
import java.util.GregorianCalendar;

/**
 * @author <your name>, <your student number>
 *
 */
public class DateUtil {
	
	public static GregorianCalendar convertFromDMY(String dd_mm_yy) {
		String[] elements = dd_mm_yy.split("-");
		if (elements == null || elements.length != 3) {
			return null;
		}
		
		int year = Integer.parseInt(elements[2]);
		int month = Integer.parseInt(elements[1]) - 1; // GregorianCalendar expects 0-based month
		int dayOfMonth = Integer.parseInt(elements[0]);
		GregorianCalendar date = new GregorianCalendar(year, month, dayOfMonth);
		return date;
		
	}

	public static String format(GregorianCalendar date) {
		if (date == null) {
			return null;
		}
		DateFormat dateFormat = DateFormat.getDateInstance(DateFormat.MEDIUM);
		return dateFormat.format(date.getTime());
	}
}