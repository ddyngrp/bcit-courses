/**
 * Project: A00683006
 * File: Student.java
 * Date: 19-Oct-07
 * Time: 7:22:33 PM
 */
package a00683006.midterm.data;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class Student {

	private String idNumber, fName, lName, email;
	
	public Student(String idNumber, String fName, String lName, String email) {
		this.idNumber = idNumber;
		this.fName = fName;
		this.lName = lName;
		this.email = email;
	}
	
	public Student(String[] data) {
		this(data[0], data[1], data[2], data[3]);
	}

	/**
	 * @return the idNumber
	 */
	public String getIdNumber() {
		return idNumber;
	}

	/**
	 * @param idNumber the idNumber to set
	 */
	public void setIdNumber(String idNumber) {
		this.idNumber = idNumber;
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
	 * @return the email
	 */
	public String getEmail() {
		return email;
	}

	/**
	 * @param email the email to set
	 */
	public void setEmail(String email) {
		this.email = email;
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
	    final String TAB = ", ";
	    
	    String retValue = "";
	    
	    retValue = "Student["
	        + this.idNumber + TAB
	        + this.fName + TAB
	        + this.lName + TAB
	        + this.email
	        + "]\n";
	
	    return retValue;
	}
}
