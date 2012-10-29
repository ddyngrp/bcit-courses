/**
 * Project: A00683006
 * File: Course.java
 * Date: 19-Oct-07
 * Time: 7:22:40 PM
 */
package a00683006.midterm.data;

import java.util.ArrayList;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class Course implements StudentManager {

	private String courseNumber, courseName;
	private Professor professor;
	private ArrayList<Student> studentList;
	
	public Course(String courseNumber, String courseName, Professor professor) {
		this.courseNumber = courseNumber;
		this.courseName = courseName;
		this.professor = professor;
		this.studentList = new ArrayList<Student>();
	}
	
	public void addStudent(Student student) {
		studentList.add(student);
	}
	
	public void dropStudent(Student student) {
		
		for (Student stud : studentList) {
			if (stud.getIdNumber().equals(student.getIdNumber())) {
				studentList.remove(stud);
			}
		}
	}

	/**
	 * @return the courseNumber
	 */
	public String getCourseNumber() {
		return courseNumber;
	}

	/**
	 * @param courseNumber the courseNumber to set
	 */
	public void setCourseNumber(String courseNumber) {
		this.courseNumber = courseNumber;
	}

	/**
	 * @return the courseName
	 */
	public String getCourseName() {
		return courseName;
	}

	/**
	 * @param courseName the courseName to set
	 */
	public void setCourseName(String courseName) {
		this.courseName = courseName;
	}

	/**
	 * @return the professor
	 */
	public Professor getProfessor() {
		return professor;
	}

	/**
	 * @param professor the professor to set
	 */
	public void setProfessor(Professor professor) {
		this.professor = professor;
	}

	/**
	 * @return the studentList
	 */
	public ArrayList<Student> getStudentList() {
		return studentList;
	}

	/**
	 * @param studentList the studentList to set
	 */
	public void setStudentList(ArrayList<Student> studentList) {
		this.studentList = studentList;
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
	    
	    retValue = "Course["
	        + this.courseNumber + TAB
	        + this.courseName + TAB
	        + this.professor + "\n "
	        + this.studentList
	        + "]";
	
	    return retValue;
	}
	
}
