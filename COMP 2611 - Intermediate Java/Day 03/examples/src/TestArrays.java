import java.util.*;

public class TestArrays {
  public static void main(String[] args) {
    // Create an array of 10 int values
    int[] array = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Fill array from index 6 to index 8 with 50
    Arrays.fill(array, 6, 8, 50);
    System.out.println("After filling, the array is");
    for (int i = 0; i < 10; i++) {
      System.out.print(array[i] + " ");
    }
    System.out.println();

    // Sort the array
    Arrays.sort(array);
    System.out.println("After sorting, the array is");
    for (int i = 0; i < 10; i++) {
      System.out.print(array[i] + " ");
    }
    System.out.println();

    // Search for 30 in the array
    System.out.println("Search 30 in the array : " +
      Arrays.binarySearch(array, 30));

    // Search for 3 in the array
    System.out.println("Search 3 in the array : " +
      Arrays.binarySearch(array, 3));

    // Search for -30 in the array
    System.out.println("Search -30 in the array : " +
      Arrays.binarySearch(array, -30));

    // Test if two arrays are the same
    int[] a = new int[10];
    System.out.println("Compare array with a : " +
      Arrays.equals(array, a));
  }
}
