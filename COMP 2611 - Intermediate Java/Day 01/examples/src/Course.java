public class Course {
  private String name;
  private String[] students = new String[100];
  private int numberOfStudents;

  public Course(String name) {
    this.name = name;
  }

  public void addStudent(String student) {
    students[numberOfStudents] = student;
    numberOfStudents++;
  }

  public String[] getStudents() {
    return students;
  }

  public int getNumberOfStudents() {
    return numberOfStudents;
  }

  public String getName() {
    return name;
  }
}
