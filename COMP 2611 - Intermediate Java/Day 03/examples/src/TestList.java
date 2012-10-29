import java.util.ArrayList;
import java.util.List;

public class TestList {
  public static void main(String[] args) {
    // Create a list
   List list = new ArrayList();

    // Add elements to the list
    list.add("America"); // Add it to the list
    System.out.println("(1) " + list);

    list.add(0, "Canada"); // Add it to the beginning of the list
    System.out.println("(2) " + list);

    list.add("Russia"); // Add it to the end of the list
    System.out.println("(3) " + list);

    list.add("France"); // Add it to the end of the list
    System.out.println("(4) " + list);

    list.add(2, "Germany"); // Add it to the list at index 2
    System.out.println("(5) " + list);

    list.add(5, "Norway"); // Add it to the list at index 5
    System.out.println("(6) " + list);

    list.add(0, "Netherlands"); // Same as list.addFirst("Daniel")
    System.out.println("(7) " + list);

    // Remove elements from the list
    list.remove("Australia"); // Same as list.remove(0) in this case
    System.out.println("(8) " + list);

    list.remove(2); // Remove the element at index 2
    System.out.println("(9) " + list);

    list.remove(list.size() - 1); // Remove the last element
    System.out.println("(10) " + list);
  }
}
