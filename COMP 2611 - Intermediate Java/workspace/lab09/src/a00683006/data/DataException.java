/**
 * Project: lab09
 * File: DataException.java
 * Date: 8-Oct-07
 * Time: 7:21:22 PM
 */
package a00683006.data;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class DataException extends Exception {
	
	private String data;
	
	/**
	 * Exception skeleton
	 * @param data
	 */
	public DataException(String data) {
		super(data);
		this.data = data;
	}
	
	/**
	 * Return the data passed to the exception
	 * @return data
	 */
	public String getData() {
		return data;
	}
}
