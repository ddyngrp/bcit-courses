import java.util.*;

public class TestCollections {
  public static void main(String[] args) {
    // Create a list of three strings
    List list = Collections.nCopies(3, "red");

    // Create an array list
    ArrayList arrayList = new ArrayList(list);
    System.out.println("The initial list is " + arrayList);
    list = null; // Release list

    // Fill in "yellow" to the list
    Collections.fill(arrayList, "yellow");
    System.out.println("After filling yellow, the list is " +
      arrayList);

    // Add three new elements to the list
    arrayList.add("white");
    arrayList.add("black");
    arrayList.add("orange");
    System.out.println("After adding new elements, the list is\n"
      + arrayList);

    // Shuffle the list
    Collections.shuffle(arrayList);
    System.out.println("After shuffling, the list is\n"
      + arrayList);

    // Find the minimum and maximum elements in the list
    System.out.println("The minimum element in the list is "
      + Collections.min(arrayList));
    System.out.println("The maximum element in the list is "
      + Collections.max(arrayList));

    // Sort the list
    Collections.sort(arrayList);
    System.out.println("The sorted list is\n" + arrayList);

    // Find an element in the list
    System.out.println("The search result for gray is " +
      Collections.binarySearch(arrayList, "gray"));

    // Create a synchronized list
    List syncList = Collections.synchronizedList(arrayList);

    // Create a synchronized read-only list
    List unmodifiableList = Collections.unmodifiableList(syncList);
    arrayList = null; // Release arrayList
    syncList = null; // Release syncList

    try {
      unmodifiableList.add("black");
    }
    catch (Exception ex) {
      System.out.println(ex);
    }
  }
}
