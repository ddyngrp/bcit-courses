/**
 * Project: lab01
 * File: Lab1.java
 * Date: 18-Sep-07
 * Time: 4:35:24 AM
 */
package a00683006.lab01;

import a00683006.lab01.data.Student;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class Lab1 {
	
	public static final String firstName = "Steffen";
	public static final String lastName = "Norgren";
	public static final String studentNumber = "A00683006";

	/**
	 * This method simply creates a new student object with sepcific variables
	 * and then runs a for loop to print out the toString information for
	 * said object 10 times.
	 * @param args
	 */
	public static void main(String[] args) {
		Student student = new Student(firstName, lastName, studentNumber);
		
		for (int i = 0; i < 10; i++) {
			System.out.println(student);
		}
	}

}
