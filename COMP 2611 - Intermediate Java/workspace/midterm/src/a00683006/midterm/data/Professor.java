/**
 * Project: A00683006
 * File: Professor.java
 * Date: 19-Oct-07
 * Time: 7:22:19 PM
 */
package a00683006.midterm.data;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class Professor {
	
	private String fName, lName;
	
	public Professor(String fName, String lName) {
		this.fName = fName;
		this.lName = lName;
	}

	/**
	 * @return the fName
	 */
	public String getFName() {
		return fName;
	}

	/**
	 * @param name the fName to set
	 */
	public void setFName(String name) {
		fName = name;
	}

	/**
	 * @return the lName
	 */
	public String getLName() {
		return lName;
	}

	/**
	 * @param name the lName to set
	 */
	public void setLName(String name) {
		lName = name;
	}

	/**
	 * Constructs a <code>String</code> with all attributes
	 * in name = value format.
	 *
	 * @return a <code>String</code> representation 
	 * of this object.
	 */
	public String toString()
	{
	    final String TAB = " ";
	    
	    String retValue = "";
	    
	    retValue = "Professor["
	        + this.fName + TAB
	        + this.lName
	        + "]";
	
	    return retValue;
	}
}
