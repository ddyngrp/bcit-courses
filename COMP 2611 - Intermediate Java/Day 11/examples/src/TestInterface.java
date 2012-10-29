// TestInterface.java: Use the Comparable interface
// and the generic max method to find max objects
public class TestInterface {
  /** Main method */
  public static void main(String[] args) {
    // Create two comparable circles
    ComparableCircle circle1 = new ComparableCircle(5);
    ComparableCircle circle2 = new ComparableCircle(4);

    // Display the max circle
    Object circle = Max.max(circle1, circle2);
    System.out.println("The max circle's radius is " +
      ((Circle)circle).getRadius());
    System.out.println(circle);
  }
}

// ComparableCircle is a subclass of Circle, which implements the
// Comparable interface
class ComparableCircle extends Circle implements Comparable {
  /** Construct a ComparableCircle with a specified radius */
  public ComparableCircle(double r) {
    super(r);
  }

  /** Implement the compareTo method defined in Comparable */
  public int compareTo(Object o) {
    if (getRadius() > ((Circle)o).getRadius())
      return 1;
    else if (getRadius() < ((Circle)o).getRadius())
      return -1;
    else
      return 0;
  }
}
