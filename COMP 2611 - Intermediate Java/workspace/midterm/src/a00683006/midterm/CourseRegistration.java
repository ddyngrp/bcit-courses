/**
 * Project: A00683006
 * File: CourseRegistration.java
 * Date: 19-Oct-07
 * Time: 7:21:27 PM
 */
package a00683006.midterm;

import a00683006.midterm.data.*;
import a00683006.midterm.util.OutputUtil;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class CourseRegistration {

	private final String[][] STUDENT_DATA = {
			{"A00000001", "Fred", "Fish", "f_f@my.bcit.ca"},
			{"A00000002", "Bullwinkle", "Moose", "bull_moose@my.bcit.ca"},
			{"A00000003", "Taboo", "Cat", "meow@my.bcit.ca"},
			{"A00000004", "Bugs", "Bunny", "wutzup_doc.bcit.ca"},
			{"A00000005", "Sylvester", "Cat", "i_like_birdthz@my.bcit.ca"},
			{"A00000006", "Daffy", "Duck", "dithpicable@my.bcit.ca"}
		};

	private final String PROF_FNAME = "Albert";
	private final String PROF_LNAME = "Einstein";
	private final String COURSE_NAME = "Nuclear Physics for Dummies";
	private final String COURSE_NUMBER = "DUMM 1011";

	private Course theCourse;
	private Professor theProf;

	/**
	 * Default constructor deliciousness.
	 */
	public CourseRegistration(){
	}

	public static void main(String[] args) {
		new CourseRegistration().test();
	}

	/**
	 * The test() method will instantiate the Course and Professor references above.
	 * A looping structure will then be used to create six Students and add them 
	 * to the class list. The class list will then be displayed.
	 * The fifth Student in the list will drop the course.
	 * Finally, the Course and Professor information will be displayed, 
	 * along with the list of Students. Use the data provided in the arrays above.
	 */
	public void test() {
		theProf = new Professor(PROF_FNAME, PROF_LNAME);
		theCourse = new Course(COURSE_NUMBER, COURSE_NAME, theProf);
		Student dropStudent;
		
		for (int i = 0; i < STUDENT_DATA.length; i++) {
			theCourse.addStudent(new Student(STUDENT_DATA[i]));
		}

		System.out.println("Students added to the Course:");
		OutputUtil.print(theCourse.getStudentList());
		
		System.out.println("The following Student has dropped the Course:");
		System.out.println(theCourse.getStudentList().get(4));
		dropStudent = theCourse.getStudentList().get(4);
		
		theCourse.dropStudent(dropStudent);

		System.out.println(theCourse);
	}
}