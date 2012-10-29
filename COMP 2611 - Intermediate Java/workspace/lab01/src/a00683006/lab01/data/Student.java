/**
 * Project: lab01
 * File: Student.java
 * Date: 18-Sep-07
 * Time: 4:35:37 AM
 */
package a00683006.lab01.data;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class Student {
	
	private String firstName;
	private String lastName;
	private String studentNumber;
	
	/**
	 * This is the default constructor for the Student class.
	 * It does absolutely nothing!
	 */
	public Student() {
	}
	
	/**
	 * This is the overloaded constructor in which variables
	 * are actually expected.
	 * @param firstName The student's first name.
	 * @param lastName The student's last name.
	 * @param studentNumber The student's student number.
	 */
	public Student(String firstName, String lastName, String studentNumber) {
		this.firstName = firstName;
		this.lastName = lastName;
		this.studentNumber = studentNumber;
	}

	/**
	 * @return the firstName
	 */
	public String getFirstName() {
		return firstName;
	}

	/**
	 * @param firstName the firstName to set
	 */
	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}

	/**
	 * @return the lastName
	 */
	public String getLastName() {
		return lastName;
	}

	/**
	 * @param lastName the lastName to set
	 */
	public void setLastName(String lastName) {
		this.lastName = lastName;
	}

	/**
	 * @return the studentNumber
	 */
	public String getStudentNumber() {
		return studentNumber;
	}

	/**
	 * @param studentNumber the studentNumber to set
	 */
	public void setStudentNumber(String studentNumber) {
		this.studentNumber = studentNumber;
	}

	/**
	 * @return a String representation of this object.
	 */
	public String toString()
	{
		return firstName + " " + lastName + ", " + studentNumber;
	}
}
